#include "MousePicker.h"

#include "Maths.h"
#include "TerraForge.h"

MousePicker::MousePicker(Camera &camera, glm::mat4 projection) : camera(camera), projectionMatrix(projection) {}

glm::vec3 MousePicker::getCurrentRay()
{
	return this->currentRay;
}

void MousePicker::update()
{
	viewMatrix = camera.getViewMatrix();
	currentRay = calculateMouseRay();
}

glm::vec3 MousePicker::calculateMouseRay()
{
	float mouseX = TerraForge::mouseX;
	float mouseY = TerraForge::mouseY;
	glm::vec2 normalizedCoords = getNormalizedDeviceCoords(mouseX, mouseY);
	glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
	glm::vec4 eyeCoords = toEyeCoords(clipCoords);
	glm::vec3 worldRay = toWorldCoords(eyeCoords);
	return worldRay;
}

glm::vec2 MousePicker::getNormalizedDeviceCoords(float mouseX, float mouseY)
{
	float x = (2.0f * mouseX) / TerraForge::SCREEN_WIDTH - 1.0f;
	float y = 1.0f - (2.0f * mouseY) / TerraForge::SCREEN_HEIGHT;
	return glm::vec2(x, y);
}

glm::vec4 MousePicker::toEyeCoords(glm::vec4 clipCoords)
{
	glm::mat4 invertedProjection = glm::inverse(projectionMatrix);
	glm::vec4 eyeCoords = invertedProjection * clipCoords;
	return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
}

glm::vec3 MousePicker::toWorldCoords(glm::vec4 eyeCoords)
{
	glm::mat4 invertedView = glm::inverse(viewMatrix);
	glm::vec4 rayWorld = invertedView * eyeCoords;
	glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
	mouseRay = glm::normalize(mouseRay);
	return mouseRay;
}