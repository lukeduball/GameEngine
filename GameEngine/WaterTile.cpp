#include "WaterTile.h"

const float WaterTile::TILE_SIZE = 40.0f;

WaterTile::WaterTile(float centerX, float height, float centerZ) : x(centerX), height(height), z(centerZ) {}

float WaterTile::getHeight()
{
	return this->height;
}

float WaterTile::getX()
{
	return this->x;
}

float WaterTile::getZ()
{
	return this->z;
}

