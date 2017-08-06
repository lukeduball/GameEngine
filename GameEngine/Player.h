#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player(TexturedModel texture, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);

	void Update();
	void Render();

	void ProcessMovementInput(GLfloat deltaTime);

	GLfloat getMovementSpeed();

	glm::vec3 getEyesPosition();

private:
	GLfloat currentSpeed = 0;
	float upwardSpeed = 0;
	const float	JUMP_SPEED = 500.0f;
	float TERRAIN_HEIGHT = 0.0f;

	bool onGround = true;

	GLfloat movementSpeed;
};