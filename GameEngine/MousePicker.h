#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

class MousePicker
{
public:
	MousePicker(Camera &camera, glm::mat4 projection);
	glm::vec3 getCurrentRay();
	void update();
private:
	glm::vec3 currentRay;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	Camera camera;

	glm::vec3 calculateMouseRay();
	glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY);
	glm::vec4 toEyeCoords(glm::vec4 clipCoords);
	glm::vec3 toWorldCoords(glm::vec4 eyeCoords);
};