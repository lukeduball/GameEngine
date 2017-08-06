#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

class RawModel
{
public:
	RawModel(GLuint id, GLuint count);

	GLuint getVAOID();
	GLuint getVertexCount();
private:
	GLuint vaoID;
	GLuint vertexCount;
};