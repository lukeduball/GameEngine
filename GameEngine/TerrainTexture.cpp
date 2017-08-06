#include "TerrainTexture.h"

TerrainTexture::TerrainTexture(GLuint id) : textureID(id) {}

GLuint TerrainTexture::getID()
{
	return this->textureID;
}