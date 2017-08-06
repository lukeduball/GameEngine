#include "Player.h"
#include "TerraForge.h"
#include "Camera.h"
#include "Terrain.h"
#include "Particle.h"
#include "ParticleRenderer.h"

Player::Player(TexturedModel texture, glm::vec3 position, float rotX, float rotY, float rotZ, float scale) : Entity(texture, position, rotX, rotY, rotZ, scale)
{
	TerraForge::thePlayer = this;
	this->movementSpeed = 70.0f;
	TerraForge::camera.updatePositionWithPlayer();
	TerraForge::camera.updateCameraVectors();
}

void Player::Update()
{
	rotationY = -glm::radians(TerraForge::camera.getYaw()) + glm::radians(90.0f);
	ProcessMovementInput(TerraForge::deltaTime);
	upwardSpeed += TerraForge::GRAVITY * TerraForge::deltaTime;
	increasePosition(glm::vec3(0, upwardSpeed, 0));
	float terrainHeight = TerraForge::currentTerrain->getHeightOfTerrain(position.x, position.z);
	if (position.y < terrainHeight)
	{
		upwardSpeed = 0;
		onGround = true;
		position.y = terrainHeight;
	}
	TerraForge::camera.updatePositionWithPlayer();
}

void Player::Render()
{

}

void Player::ProcessMovementInput(GLfloat deltaTime)
{
	GLfloat velocity = this->movementSpeed * deltaTime;
	glm::vec3 frontVector = TerraForge::camera.getFrontMove();
	glm::vec3 rightVector = TerraForge::camera.getRightMove();
	if (TerraForge::freeCamera)
	{
		frontVector = TerraForge::camera.getFront();
		rightVector = TerraForge::camera.getRight();
	}

	if (TerraForge::keys[GLFW_KEY_W])
	{
		this->position += frontVector * velocity;
	}

	if (TerraForge::keys[GLFW_KEY_S])
	{
		this->position -= frontVector * velocity;
	}

	if (TerraForge::keys[GLFW_KEY_A])
	{
		this->position -= rightVector * velocity;
	}

	if (TerraForge::keys[GLFW_KEY_D])
	{
		this->position += rightVector * velocity;
	}

	if (TerraForge::keys[GLFW_KEY_SPACE])
	{
		if (onGround)
		{
			upwardSpeed += JUMP_SPEED  * TerraForge::deltaTime;
			onGround = false;
		}
	}

	if (TerraForge::keys[GLFW_KEY_Y])
	{
		
	}
}

GLfloat Player::getMovementSpeed()
{
	return this->movementSpeed;
}

glm::vec3 Player::getEyesPosition()
{
	return position + glm::vec3(0.0f, 8.0f, 0.0f);
}