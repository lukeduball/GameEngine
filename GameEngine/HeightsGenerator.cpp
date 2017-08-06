#include "HeightsGenerator.h"

#include <iostream>
#include <math.h>
#include "Maths.h"

HeightsGenerator::HeightsGenerator() : seed(std::uniform_int_distribution<int>(0, 1000000000)(random)), gen(std::uniform_real_distribution<float>(-1.0f, 1.0f))
{

}

float HeightsGenerator::generateHeight(int x, int z)
{
	float total = 0;
	float d = (float)pow(2, OCTAVES - 1);
	for (int i = 0; i < OCTAVES; i++)
	{
		float frequency = (float)(pow(2, i) / d);
		float amp = (float)pow(ROUGHNESS, i) * AMPLITUDE;
		total += getInterpolatedNoise(x * frequency, z * frequency) * amp;
	}
	total += getInterpolatedNoise(x / 2.0f, z / 2.0f) * AMPLITUDE / 3.0f;
	total += getInterpolatedNoise(x / 2.0f, z / 2.0f) * AMPLITUDE / 9.0f;
	return total;
}

float HeightsGenerator::getNoise(int x, int z)
{
	random.seed(x * 49632 + z * 325176 + seed);
	return gen(random);
}

float HeightsGenerator::getSmoothNoise(int x, int z)
{
	float cornors = (getNoise(x-1, z-1) + getNoise(x+1, z+1) + getNoise(x-1, z+1) + getNoise(x+1, z-1)) / 16.0f;
	float sides = (getNoise(x + 1, z) + getNoise(x - 1, z) + getNoise(x, z + 1) + getNoise(x, z - 1)) / 8.0f;
	float center = getNoise(x, z) / 4.0f;
	return cornors + sides + center;
}

float HeightsGenerator::interpolate(float a, float b, float blend)
{
	double theta = blend * Maths::PI;
	float f = (float)(1.0f - cos(theta)) * 0.5f;
	return a * (1.0f - f) + b * f;
}

float HeightsGenerator::getInterpolatedNoise(float x, float z)
{
	int intX = (int)x;
	int intZ = (int)z;
	float fracX = x - intX;
	float fracZ = z - intZ;

	float v1 = getSmoothNoise(intX, intZ);
	float v2 = getSmoothNoise(intX + 1, intZ);
	float v3 = getSmoothNoise(intX, intZ + 1);
	float v4 = getSmoothNoise(intX + 1, intZ + 1);
	float i1 = interpolate(v1, v2, fracX);
	float i2 = interpolate(v3, v4, fracX);
	return interpolate(i1, i2, fracZ);
}