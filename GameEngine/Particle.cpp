#include "Particle.h"
#include "TerraForge.h"
#include "ParticleRenderer.h"
#include "Camera.h"

Particle::Particle(ParticleTexture &texture, glm::vec3 position, glm::vec3 vel, float gravEffect, float life, float rotation, float scale) :
	tex(texture), position(position), velocity(vel), gravityEffect(gravEffect), lifeLength(life), rotation(rotation), scale(scale)
{
	TerraForge::particleRenderer->addParticle(this);
}

glm::vec3 Particle::getPosition()
{
	return this->position;
}

float Particle::getRotation()
{
	return this->rotation;
}

float Particle::getScale()
{
	return this->scale;
}

bool Particle::update()
{
	velocity.y += TerraForge::GRAVITY * gravityEffect * TerraForge::deltaTime;
	glm::vec3 change = glm::vec3(velocity);
	change *= TerraForge::deltaTime;
	position = position + change;
	distanceFromCamera = glm::length(TerraForge::camera.getPosition() - position) * glm::length(TerraForge::camera.getPosition() - position);
	updateTextureCoordInfo();
	elapsedTime += TerraForge::deltaTime;
	return elapsedTime < lifeLength;
}

ParticleTexture Particle::getTexture()
{
	return this->tex;
}

glm::vec2 Particle::getIndex1()
{
	return this->index1;
}

glm::vec2 Particle::getIndex2()
{
	return this->index2;
}

float Particle::getBlendFactor()
{
	return this->blendFactor;
}

float Particle::getDistaceFromCamera()
{
	return this->distanceFromCamera;
}

void Particle::updateTextureCoordInfo()
{
	float lifeFactor = elapsedTime / lifeLength;
	int stageCount = tex.getNumberOfRows()  * tex.getNumberOfRows();
	float atlasProgression = lifeFactor * stageCount;
	int index = (int)floor(atlasProgression);
	int nextIndex = index < stageCount - 1 ? index + 1 : index;
	this->blendFactor = fmodf(atlasProgression, 1);
	setTextureOffset(index1, index);
	setTextureOffset(index2, nextIndex);
}

void Particle::setTextureOffset(glm::vec2 &offset, int index)
{
	int column = index % tex.getNumberOfRows();
	int row = index / tex.getNumberOfRows();
	offset.x = (float)column / tex.getNumberOfRows();
	offset.y = (float)row / tex.getNumberOfRows();
}

#pragma region ParticleTexture

ParticleTexture::ParticleTexture(int textureID, int numberOfRows) : textureID(textureID), numberOfRows(numberOfRows), particleID(nextParticle)
{
	nextParticle++;
}

int ParticleTexture::getTexture() 
{
	return this->textureID;
}

int ParticleTexture::getNumberOfRows()
{
	return this->numberOfRows;
}

int ParticleTexture::nextParticle = 0;

#pragma endregion