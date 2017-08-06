#pragma once

#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Loader.h"
#include "RawModel.h"
#include "TerrainTexturePack.h"

class HeightsGenerator;

class Terrain
{
public:
	Terrain(int gridX, int gridZ, Loader loader, TerrainTexturePack texture, TerrainTexture blendMap, GLchar *fileName);

	float getX();
	float getZ();
	RawModel getModel();
	TerrainTexturePack *getTexturePack();
	TerrainTexture *getBlendMap();

	float getHeightOfTerrain(float worldX, float worldZ);

	std::vector<std::vector<float>> heights;

private:
	const float SIZE = 800;
	const float MAX_HEIGHT = 70;
	const float MAX_PIXEL_COLOR = 256 * 256 * 256;

	float x;
	float z;
	RawModel model;
	TerrainTexturePack texturePack;
	TerrainTexture blendMap;

	RawModel generateTerrain(Loader loader, GLchar *fileName);
	float getHeight(int x, int y, unsigned char *image, int size);
	float getHeight(int x, int z, HeightsGenerator &generator);
	glm::vec3 calculateNormal(int x, int z, HeightsGenerator &generator);
	glm::vec3 calculateNormal(int x, int y, unsigned char *image, int size);
};