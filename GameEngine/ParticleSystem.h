#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <random>

#include "Particle.h"

class ParticleSystem
{
public:
	ParticleSystem(ParticleTexture &texture, float pps, float speed, float gravFactor, float life, float scale);
	void setDirection(glm::vec3 direction, float deviation);
	void randomRotation();
	void setSpeedOffset(float randFactor);
	void setLifeOffset(float randFactor);
	void setScaleOffset(float randFactor);
	void spawnParticles(glm::vec3 centerPosition);
private:
	ParticleTexture texture;
	float particlesPerSecond, speed, gravityFactor, lifeLength, scale;
	bool randRotation;
	float speedOffset, lifeOffset, scaleOffset;
	glm::vec3 direction;
	float directionDeviation = 0;
	std::default_random_engine random;

	void emitParticle(glm::vec3 centerPosition);
	float generateValue(float var, float randFactor);
	float generateRotation();
	glm::vec3 generateRandomUnitVectorWithinCone(glm::vec3 direction, float angle);
	glm::vec3 generateRandomUnitVector();

};