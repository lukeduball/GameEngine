#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ParticleTexture
{
public:
	ParticleTexture(int textureID, int numberOfRows);
	int getTexture();
	int getNumberOfRows();
	int particleID = 0;
	static int nextParticle;

private:
	int textureID;
	int numberOfRows;
};

class Particle
{
public:
	Particle(ParticleTexture &texture, glm::vec3 position, glm::vec3 vel, float gravEffect, float life, float rotation, float scale);
	glm::vec3 getPosition();
	float getRotation();
	float getScale();
	bool update();
	ParticleTexture getTexture();
	glm::vec2 getIndex1();
	glm::vec2 getIndex2();
	float getBlendFactor();
	float getDistaceFromCamera();

private:
	ParticleTexture tex;
	glm::vec3 position;
	glm::vec3 velocity;
	float gravityEffect;
	float lifeLength;
	float rotation;
	float scale;
	float distanceFromCamera;

	float elapsedTime = 0;

	glm::vec2 index1;
	glm::vec2 index2;
	float blendFactor;

	void updateTextureCoordInfo();
	void setTextureOffset(glm::vec2 &offset, int index);
};