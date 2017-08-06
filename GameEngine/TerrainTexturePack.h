#pragma once

#include "TerrainTexture.h"

class TerrainTexturePack
{
public:
	TerrainTexturePack(TerrainTexture background, TerrainTexture r, TerrainTexture g, TerrainTexture b);
	TerrainTexture getBackgroundTexture();
	TerrainTexture getRTexture();
	TerrainTexture getGTexture();
	TerrainTexture getBTexture();
private:
	TerrainTexture backgroundTexture;
	TerrainTexture rTexture;
	TerrainTexture gTexture;
	TerrainTexture bTexture;

};