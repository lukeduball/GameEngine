#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

class TerrainTexture 
{
public:
	TerrainTexture(GLuint id);
	GLuint getID();
private:
	GLuint textureID;
};