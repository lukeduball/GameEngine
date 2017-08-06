#pragma once
class WaterTile
{
public:
	WaterTile(float centerX, float height, float centerZ);
	float getHeight();
	float getX();
	float getZ();

	static const float TILE_SIZE;

private:
	float height;
	float x, z;
};

