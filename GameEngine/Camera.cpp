#include "Camera.h"
#include "TerraForge.h"
#include "Player.h"
#include "Terrain.h"

glm::mat4 Camera::getViewMatrix()
{		
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch)
{
	xOffset *= this->mouseSensitivity;
	yOffset *= this->mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (constrainPitch)
	{
		if (pitch > 89.0f)
		{
			pitch = 89.0f;
		}

		if (pitch < -89.0f)
		{
			pitch = -89.0f;
		}
	}

	this->updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yOffset)
{
	if (this->distanceFromPlayer >= 1.0f && this->distanceFromPlayer <= 400.0f)
	{
		this->distanceFromPlayer -= yOffset * 2;
	}

	if (this->distanceFromPlayer < 1.0f)
	{
		this->distanceFromPlayer = 1.0f;
	}

	if (this->distanceFromPlayer > 400.0f)
	{
		this->distanceFromPlayer = 400.0f;
	}
}

GLfloat Camera::GetZoom() const
{
	return this->zoom;
}

glm::vec3 Camera::getPosition()
{
	return this->position;
}

void Camera::setPosition(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 Camera::getFront()
{
	return this->front;
}

glm::vec3 Camera::getUp()
{
	return this->up;
}

glm::vec3 Camera::getRight()
{
	return this->right;
}

glm::vec3 Camera::getFrontMove()
{
	return this->frontMove;
}

glm::vec3 Camera::getRightMove()
{
	return this->rightMove;
}

float Camera::getDistanceFromPlayer()
{
	return this->distanceFromPlayer;
}

float Camera::getYaw()
{
	return yaw;
}

float Camera::getPitch()
{
	return pitch;
}

void Camera::invertPitch()
{
	pitch = -pitch;
	this->updateCameraVectors();
}

void Camera::updatePositionWithPlayer()
{
	glm::vec3 playerEyesPosition = TerraForge::thePlayer->getPosition() - glm::vec3(0.0f, -8.0f, 0.0f);
	this->position = (playerEyesPosition - (this->front * glm::vec3(distanceFromPlayer)));
}

void Camera::updateCameraVectors()
{
	Player *player = TerraForge::thePlayer;
	glm::vec3 frontMove;
	frontMove.x = cos(glm::radians(yaw));
	frontMove.z = sin(glm::radians(yaw));
	this->frontMove = glm::normalize(frontMove);
	this->rightMove = glm::normalize(glm::cross(this->frontMove, this->worldUp));

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	this->front = glm::normalize(front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}