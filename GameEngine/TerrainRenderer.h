#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <list>

#include "TerrainShader.h"
#include "Terrain.h"
#include "TexturedModel.h"

class TerrainRenderer
{
public:
	TerrainRenderer(TerrainShader &shader, glm::mat4 projectionMatrix);

	void render(std::list<Terrain> terrains);

private:
	TerrainShader shader;

	void prepareTerrainModel(Terrain *terrain);
	void bindTextures(Terrain *terrain);
	void modelMatrix(Terrain *terrain);
	void unbindTexturedModel();
};