#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

#include "RawModel.h"

class Loader;

class OBJLoader
{
public:
	static RawModel loadObjModel(std::string fileName, Loader loader);
	static RawModel loadModel(std::string fileName, Loader loader);
	
private:
	static void processVertex(std::vector<std::string> vertexData, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals, std::vector<GLuint> &indices, std::vector<GLfloat> &textureData, std::vector<GLfloat> &normalsData);
};