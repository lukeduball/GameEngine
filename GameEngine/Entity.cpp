#include "Entity.h"

Entity::Entity(TexturedModel &model, glm::vec3 position, float rotationX, float rotationY, float rotationZ, float scale) : Entity(model, 0, position, rotationX, rotationY, rotationZ, scale) {}
Entity::Entity(TexturedModel &model, int texIndex, glm::vec3 position, float rotationX, float rotationY, float rotationZ, float scale) : model(model), textureIndex(texIndex), position(position), rotationX(rotationX), rotationY(rotationY), rotationZ(rotationZ), scale(scale) {}

void Entity::Update()
{

}

void Entity::increasePosition(glm::vec3 movement)
{
	position += movement;
}

void Entity::increaseRotation(float x, float y, float z)
{
	this->rotationX += x;
	this->rotationY += y;
	this->rotationZ += z;
}

TexturedModel Entity::getModel()
{
	return model;
}

glm::vec3 Entity::getPosition()
{
	return position;
}

float Entity::getRotationX()
{
	return rotationX;
}

float Entity::getRotationY()
{
	return rotationY;
}

float Entity::getRotationZ()
{
	return rotationZ;
}

float Entity::getScale()
{
	return scale;
}

float Entity::getTextureXOffset()
{
	int column = textureIndex % model.getTexture()->getNumberOfRows();
	return (float)column / (float)model.getTexture()->getNumberOfRows();
}

float Entity::getTextureYOffset()
{
	int row = textureIndex / model.getTexture()->getNumberOfRows();
	return (float)row / (float)model.getTexture()->getNumberOfRows();
}