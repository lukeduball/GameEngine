#pragma once

#include <random>
#include <time.h>

class HeightsGenerator
{
public:
	HeightsGenerator();
	float generateHeight(int x, int z);

private:
	const float AMPLITUDE = 40.0f;
	const int OCTAVES = 2;
	const float ROUGHNESS = 0.3f;
	std::default_random_engine random;
	std::uniform_real_distribution<float> gen;
	int seed;

	float getNoise(int x, int z);
	float getSmoothNoise(int x, int z);
	float interpolate(float a, float b, float blend);
	float getInterpolatedNoise(float x, float z);
};