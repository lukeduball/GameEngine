#include "Terrain.h"
#include "Maths.h"
#include "HeightsGenerator.h"

#include <SOIL2/SOIL2.h>
#include <iostream>
#include <cmath>

Terrain::Terrain(int gridX, int gridZ, Loader loader, TerrainTexturePack texturePack, TerrainTexture blendMap, GLchar *fileName) : texturePack(texturePack), blendMap(blendMap), x(gridX * SIZE), z(gridZ * SIZE), model(generateTerrain(loader, fileName))
{
}

float Terrain::getX()
{
	return this->x;
}

float Terrain::getZ()
{
	return this->z;
}

RawModel Terrain::getModel()
{
	return this->model;
}

TerrainTexturePack* Terrain::getTexturePack()
{
	return &this->texturePack;
}

TerrainTexture* Terrain::getBlendMap()
{
	return &this->blendMap;
}

float Terrain::getHeightOfTerrain(float worldX, float worldZ)
{
	float terrainX = worldX - this->x;
	float terrainZ = worldZ - this->z;
	float gridSquareSize = SIZE / (float)(heights.size() - 1);
	int gridX = (int)std::floor(terrainX / gridSquareSize);
	int gridZ = (int)std::floor(terrainZ / gridSquareSize);
	if (gridX >= heights.size() - 1 || gridZ >= heights.size() - 1 || gridX < 0 || gridZ < 0)
	{
		return 0;
	}
	float xCoord = std::fmod(terrainX,gridSquareSize) / gridSquareSize;
	float zCoord = std::fmod(terrainZ, gridSquareSize) / gridSquareSize;
	float answer;
	if (xCoord <= (1 - zCoord))
	{
		answer = Maths::barryCentric(glm::vec3(0, heights[gridX][gridZ], 0), glm::vec3(1, heights[gridX + 1][gridZ], 0), glm::vec3(0, heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
	}
	else
	{
		answer = Maths::barryCentric(glm::vec3(1, heights[gridX + 1][gridZ], 0), glm::vec3(1, heights[gridX + 1][gridZ + 1], 1), glm::vec3(0, heights[gridX][gridZ + 1], 1), glm::vec2(xCoord, zCoord));
	}
	return answer;
}

RawModel Terrain::generateTerrain(Loader loader, GLchar *fileName)
{
	HeightsGenerator generator = HeightsGenerator();

	int width, height;
	unsigned char *image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);

	int VERTEX_COUNT = height;
	int count = VERTEX_COUNT * VERTEX_COUNT;

	heights.resize(VERTEX_COUNT);
	for (int i = 0; i < VERTEX_COUNT; i++)
	{
		heights[i].resize(VERTEX_COUNT);
	}

	std::vector<GLfloat> vertices = std::vector<GLfloat>(count * 3);
	std::vector<GLfloat> normals = std::vector<GLfloat>(count * 3);
	std::vector<GLfloat> textureCoords = std::vector<GLfloat>(count * 2);
	std::vector<GLuint> indices = std::vector<GLuint>(6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1));
	int vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++)
	{
		for (int j = 0; j < VERTEX_COUNT; j++)
		{
			vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			float h = getHeight(j, i, image, height);
			heights[j][i] = h;
			vertices[vertexPointer * 3 + 1] = h;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			glm::vec3 normal = calculateNormal(j, i, image, height);
			normals[vertexPointer * 3] = normal.x;
			normals[vertexPointer * 3 + 1] = normal.y;
			normals[vertexPointer * 3 + 2] = normal.z;
			textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++)
	{
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++)
		{
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	SOIL_free_image_data(image);
	return loader.loadToVAO(vertices, textureCoords, normals, indices);
}

float Terrain::getHeight(int x, int z, HeightsGenerator &generator)
{
	return generator.generateHeight(x, z);
}

glm::vec3 Terrain::calculateNormal(int x, int z, HeightsGenerator &generator)
{
	float heightL = getHeight(x - 1, z, generator);
	float heightR = getHeight(x + 1, z, generator);
	float heightD = getHeight(x, z - 1, generator);
	float heightU = getHeight(x, z + 1, generator);
	glm::vec3 normal = glm::vec3(heightL - heightR, 2.0f, heightD - heightU);
	normal = glm::normalize(normal);
	return normal;
}

//This method is for heightmaps
float Terrain::getHeight(int x, int y, unsigned char *image, int size)
{
	if (x < 0 || x >= size || y < 0 || y >= size)
	{
		return 0;
	}
	float r = image[4*(x+ y*size)];
	float g = image[4 * (x + y*size) + 1];
	float b = image[4 * (x + y*size) + 2];
	float height = (r * 65536.0f) + (g * 256.0f) + b;
	height -= MAX_PIXEL_COLOR/2.0f;
	height /= MAX_PIXEL_COLOR;
	height *= 2;
	height *= MAX_HEIGHT;
	return height;
}

//This method is for heightmaps
glm::vec3 Terrain::calculateNormal(int x, int y, unsigned char *image, int size)
{
	float heightL = getHeight(x - 1, z, image, size);
	float heightR = getHeight(x + 1, z, image, size);
	float heightD = getHeight(x, z - 1, image, size);
	float heightU = getHeight(x, z + 1, image, size);
	glm::vec3 normal = glm::vec3(heightL - heightR, 2.0f, heightD - heightU);
	normal = glm::normalize(normal);
	return normal;
}