#pragma once

#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const GLfloat SENSITIVITY = 0.25f;
const GLfloat ZOOM = 45.0f;

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f)) : front(glm::vec3(0.0f, 0.0f, -1.0f)), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
	{
		this->position = position;
		this->worldUp = up;
		this->yaw = -90.0f;
		this->pitch = -40.0f;
	}

	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
	{
		this->position = glm::vec3(posX, posY, posZ);
		this->worldUp = glm::vec3(upX, upY, upZ);
	}

	glm::mat4 getViewMatrix();

	void ProcessMouseMovement(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);

	void ProcessMouseScroll(GLfloat yOffset);

	GLfloat GetZoom() const;
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	glm::vec3 getFront();
	glm::vec3 getUp();
	glm::vec3 getRight();
	glm::vec3 getFrontMove();
	glm::vec3 getRightMove();
	float getPitch();
	void invertPitch();
	float getYaw();
	float getDistanceFromPlayer();
	void updateCameraVectors();
	void updatePositionWithPlayer();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 frontMove;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 rightMove;
	glm::vec3 worldUp;

	float pitch;
	float yaw;
	GLfloat mouseSensitivity;
	GLfloat zoom;
	GLfloat distanceFromPlayer = 40.0f;
};