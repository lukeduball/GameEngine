#include "TerrainTexturePack.h"

TerrainTexturePack::TerrainTexturePack(TerrainTexture background, TerrainTexture r, TerrainTexture g, TerrainTexture b) : backgroundTexture(background), rTexture(r), gTexture(g), bTexture(b) {}

TerrainTexture TerrainTexturePack::getBackgroundTexture()
{
	return this->backgroundTexture;
}

TerrainTexture TerrainTexturePack::getRTexture()
{
	return this->rTexture;
}

TerrainTexture TerrainTexturePack::getGTexture()
{
	return this->gTexture;
}

TerrainTexture TerrainTexturePack::getBTexture()
{
	return this->bTexture;
}