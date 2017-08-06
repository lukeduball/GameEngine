#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TexturedModel.h"

class Entity
{
public:
	Entity(TexturedModel &model, int texIndex, glm::vec3 position, float rotationX, float rotationY, float rotationZ, float scale);
	Entity(TexturedModel &model, glm::vec3 position, float rotationX, float rotationY, float rotationZ, float scale);

	virtual void Update();

	void increasePosition(glm::vec3 movement);

	void increaseRotation(float x, float y, float z);

	TexturedModel getModel();

	glm::vec3 getPosition();

	float getRotationX();

	float getRotationY();

	float getRotationZ();

	float getScale();

	float getTextureXOffset();
	float getTextureYOffset();

protected:
	glm::vec3 position;
	float rotationX, rotationY, rotationZ;

private:
	TexturedModel model;
	float scale;
	int textureIndex;
};