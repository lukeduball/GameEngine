#include "ParticleSystem.h"

#include "TerraForge.h"
#include "Maths.h"

#include <math.h>
#include <time.h>

ParticleSystem::ParticleSystem(ParticleTexture &texture, float pps, float speed, float gravFactor, float life, float scale) : texture(texture), particlesPerSecond(pps), speed(speed), gravityFactor(gravFactor), lifeLength(life), scale(scale)
{
	random.seed(time(0));
}

void ParticleSystem::setDirection(glm::vec3 direction, float deviation)
{
	this->direction = direction;
	this->directionDeviation = deviation;
}

void ParticleSystem::randomRotation()
{
	this->randRotation = true;
}

void ParticleSystem::setSpeedOffset(float randFactor)
{
	this->speedOffset = randFactor * speed;
}

void ParticleSystem::setLifeOffset(float randFactor)
{
	this->lifeOffset = randFactor * lifeLength;
}

void ParticleSystem::setScaleOffset(float randFactor)
{
	this->scaleOffset = randFactor * scale;
}

void ParticleSystem::spawnParticles(glm::vec3 centerPosition)
{
	float particlesToSpawn = particlesPerSecond * TerraForge::deltaTime;
	int count = (int)floor(particlesToSpawn);
	float partialParticle = fmod(particlesToSpawn, 1);
	for (int i = 0; i < count; i++)
	{
		emitParticle(centerPosition);
	}
}

void ParticleSystem::emitParticle(glm::vec3 centerPosition)
{
	glm::vec3 velocity = glm::vec3();
	if (direction == glm::vec3(0))
	{
		velocity = generateRandomUnitVector();
	}
	else
	{
		velocity = generateRandomUnitVectorWithinCone(direction, directionDeviation);
	}
	velocity = glm::normalize(velocity);
	velocity *= generateValue(speed, speedOffset);
	float scaleAmount = generateValue(scale, scaleOffset);
	float life = generateValue(lifeLength, lifeOffset);
	new Particle(texture, glm::vec3(centerPosition), velocity, gravityFactor, life, generateRotation(), scaleAmount);
}

float ParticleSystem::generateValue(float var, float randFactor)
{
	std::uniform_real_distribution<float> gen(0.0f, 1.0f);
	float offset = (gen(random) - 0.5f) * 2.0f * randFactor;
	return var + offset;
}

float ParticleSystem::generateRotation()
{
	if (randRotation)
	{
		std::uniform_real_distribution<float> gen(0.0f, 1.0f);
		return gen(random) * 360.0f;
	}
	return 0;
}

glm::vec3 ParticleSystem::generateRandomUnitVectorWithinCone(glm::vec3 direction, float angle)
{
	float cosAngle = (float)cos(angle);
	std::uniform_real_distribution<float> gen(0.0f, 1.0f);
	float theta = gen(random) * 2.0f * Maths::PI_F;
	float z = cosAngle + (gen(random) * (1 - cosAngle));
	float rootOneMinusZSquared = (float)sqrt(1 - z * z);
	float x = (float)(rootOneMinusZSquared * cos(theta));
	float y = (float)(rootOneMinusZSquared * sin(theta));

	glm::vec4 direction1 = glm::vec4(x, y, z, 1.0f);
	if (direction1.x != 0 || direction1.y != 0 || (direction1.z != 1 && direction1.z != -1))
	{
		glm::vec3 rotateAxis = glm::cross(direction, glm::vec3(0.0f, 0.0f, 1.0f));
		rotateAxis = glm::normalize(rotateAxis);
		float rotateAngle = acos(glm::dot(direction, glm::vec3(0.0f, 0.0f, 1.0f)));
		glm::mat4 rotationMatrix = glm::mat4();
		rotationMatrix = glm::rotate(rotationMatrix, -rotateAngle, rotateAxis);
		direction1 = rotationMatrix * direction1;
	}
	else if (direction.z == -1)
	{
		direction.z *= -1;
	}
	return glm::vec3(direction1);
}

glm::vec3 ParticleSystem::generateRandomUnitVector()
{
	std::uniform_real_distribution<float> gen(0.0f, 1.0f);
	float theta = gen(random) * 2.0f * Maths::PI_F;
	float z = (gen(random) * 2.0f) - 1;
	float rootOneMinusZSquared = (float)sqrt(1 - z * z);
	float x = (float)(rootOneMinusZSquared * cos(theta));
	float y = (float)(rootOneMinusZSquared * sin(theta));
	return glm::vec3(x, y, z);
}