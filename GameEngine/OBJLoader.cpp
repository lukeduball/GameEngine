#include "OBJLoader.h"
#include "Loader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <iterator>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "StringHelper.h"

RawModel OBJLoader::loadModel(std::string fileName, Loader loader)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile("resources/models/" + fileName + ".obj", aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
	}

	aiMesh *mesh = scene->mMeshes[0];
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> textureUVS;
	std::vector<GLfloat> normals;
	std::vector<GLuint> indices;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.push_back(mesh->mVertices[i].x);
		vertices.push_back(mesh->mVertices[i].y);
		vertices.push_back(mesh->mVertices[i].z);

		normals.push_back(mesh->mNormals[i].x);
		normals.push_back(mesh->mNormals[i].y);
		normals.push_back(mesh->mNormals[i].z);

		if (mesh->mTextureCoords[0])
		{
			textureUVS.push_back(mesh->mTextureCoords[0][i].x);
			textureUVS.push_back(mesh->mTextureCoords[0][i].y);
		}
	}

	// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return loader.loadToVAO(vertices, textureUVS, normals, indices);
}

RawModel OBJLoader::loadObjModel(std::string fileName, Loader loader)
{
	std::string objCode;
	std::ifstream objFile;
	objFile.exceptions(std::ifstream::badbit);
	try 
	{
		objFile.open("resources/models/"+fileName+".obj");
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "FILE " << fileName << " NOT READ CORRECTLY" << std::endl;
	}
	std::string line;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<GLuint> indices;

	std::vector<GLfloat> textureData;
	std::vector<GLfloat> normalsData;
	int lineNumb = 0;
	try 
	{
		if (objFile.is_open())
		{
			bool firstF = true;
			while (getline(objFile, line))
			{
				std::cout << "LOADING: " << lineNumb << std::endl;
				std::vector<std::string> currentLine = StringHelper::split(line, " ");
				if (StringHelper::startsWith(line, "v "))
				{
					//Vertices
					vertices.push_back(glm::vec3(stof(currentLine[1]), stof(currentLine[2]), stof(currentLine[3])));
				}
				else if (StringHelper::startsWith(line, "vt "))
				{
					//Textures
					textures.push_back(glm::vec2(stof(currentLine[1]), stof(currentLine[2])));
				}
				else if (StringHelper::startsWith(line, "vn "))
				{
					//Normals
					normals.push_back(glm::vec3(stof(currentLine[1]), stof(currentLine[2]), stof(currentLine[3])));
				}
				else if (StringHelper::startsWith(line, "f "))
				{
					if (firstF)
					{
						textureData = std::vector<GLfloat>(vertices.size() * 2);
						normalsData = std::vector<GLfloat>(vertices.size() * 3);
						firstF = false;
					}
					std::vector<std::string> vertex1 = StringHelper::split(currentLine[1], "/");
					std::vector<std::string> vertex2 = StringHelper::split(currentLine[2], "/");
					std::vector<std::string> vertex3 = StringHelper::split(currentLine[3], "/");
					
					processVertex(vertex1, textures, normals, indices, textureData, normalsData);
					processVertex(vertex2, textures, normals, indices, textureData, normalsData);
					processVertex(vertex3, textures, normals, indices, textureData, normalsData);
				}
				lineNumb++;
			}
			objFile.close();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR READING DATA IN OBJ FILE" << std::endl;
	}

	std::vector<GLfloat> verticesData = std::vector<GLfloat>(vertices.size() * 3);
	int vertexIndex = 0;
	for (glm::vec3 vertex : vertices)
	{
		verticesData[vertexIndex++] = vertex.x;
		verticesData[vertexIndex++] = vertex.y;
		verticesData[vertexIndex++] = vertex.z;
	}

	return loader.loadToVAO(verticesData, textureData, normalsData, indices);
	
}

void OBJLoader::processVertex(std::vector<std::string> vertexData, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals,
	std::vector<GLuint> &indices, std::vector<GLfloat> &textureData, std::vector<GLfloat> &normalsData)
{
	int currentVertexPointer = std::stoi(vertexData[0]) - 1;
	indices.push_back(currentVertexPointer);
	glm::vec2 currentTex = textures[std::stoi(vertexData[1]) - 1];
	textureData[currentVertexPointer * 2] = currentTex.x;
	textureData[currentVertexPointer * 2 + 1] = 1 - currentTex.y;
	glm::vec3 currentNorm = normals[std::stoi(vertexData[2]) - 1];
	normalsData[currentVertexPointer * 3] = currentNorm.x;
	normalsData[currentVertexPointer * 3 + 1] = currentNorm.y;
	normalsData[currentVertexPointer * 3 + 2] = currentNorm.z;
}