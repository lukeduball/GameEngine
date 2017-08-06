#include "ShadowBox.h"
#include "TerraForge.h"
#include "Camera.h"
#include "MasterRenderer.h"	
#include <math.h>

const float ShadowBox::SHADOW_DISTANCE = 100.0f;
const glm::vec4 ShadowBox::UP = glm::vec4(0.0, 1.0, 0.0, 0.0);
const glm::vec4 ShadowBox::FORWARD = glm::vec4(0.0, 0.0, -1.0, 0.0);
const float ShadowBox::OFFSET = 10.0f;

ShadowBox::ShadowBox(glm::mat4 &lightViewMatrix) : lightViewMatrix(lightViewMatrix)
{
}

void ShadowBox::update()
{
	Camera *camera = &TerraForge::camera;
	glm::vec3 toNear = camera->getFront() * MasterRenderer::NEAR_PLANE;
	glm::vec3 toFar = camera->getFront() * SHADOW_DISTANCE;
	glm::vec3 centerNear = toNear + camera->getPosition();
	glm::vec3 centerFar = toFar + camera->getPosition();
	glm::vec3 farTop = centerFar + (camera->getUp() * farHeight);
	glm::vec3 farBottom = centerFar + (-camera->getUp() * farHeight);
	glm::vec3 nearTop = centerNear + (camera->getUp() * nearHeight);
	glm::vec3 nearBottom = centerNear + (-camera->getUp() * nearHeight);
	
	std::vector<glm::vec4> points = calculateFrustumVertices(centerNear, centerFar);
	bool first = true;
	for (glm::vec4 point : points) {
		if (first) {
			minX = point.x;
			maxX = point.x;
			minY = point.y;
			maxY = point.y;
			minZ = point.z;
			maxZ = point.z;
			first = false;
			continue;
		}
		if (point.x > maxX) {
			maxX = point.x;
		}
		else if (point.x < minX) {
			minX = point.x;
		}
		if (point.y > maxY) {
			maxY = point.y;
		}
		else if (point.y < minY) {
			minY = point.y;
		}
		if (point.z > maxZ) {
			maxZ = point.z;
		}
		else if (point.z < minZ) {
			minZ = point.z;
		}
	}
	maxZ += OFFSET;

}

glm::vec3 ShadowBox::getCenter()
{
	float x = (minX + maxX) / 2.0f;
	float y = (minY + maxY) / 2.0f;
	float z = (minZ + maxZ) / 2.0f;
	glm::vec4 cen = glm::vec4(x, y, z, 1.0f);
	glm::mat4 invertedLight = glm::mat4();
	invertedLight = glm::inverse(lightViewMatrix);
	return glm::vec3(invertedLight * cen);
}

float ShadowBox::getWidth()
{
	return maxX - minX;
}

float ShadowBox::getHeight()
{
	return maxY - minY;
}

float ShadowBox::getLength()
{
	return maxZ - minZ;
}

void ShadowBox::calculateWidthsAndHeights()
{
	farWidth = (float)(SHADOW_DISTANCE * tan(glm::radians(MasterRenderer::FOV)));
	nearWidth = (float)(MasterRenderer::NEAR_PLANE * tan(glm::radians(MasterRenderer::FOV)));
	farHeight = farWidth / (TerraForge::SCREEN_WIDTH / TerraForge::SCREEN_HEIGHT);
	nearHeight = nearWidth / (TerraForge::SCREEN_WIDTH / TerraForge::SCREEN_HEIGHT);
}

std::vector<glm::vec4> ShadowBox::calculateFrustumVertices(glm::vec3 centerNear, glm::vec3 centerFar)
{
	glm::vec3 upVector = TerraForge::camera.getUp();
	glm::vec3 rightVector = TerraForge::camera.getRight();
	glm::vec3 leftVector = glm::vec3(-rightVector.x, -rightVector.y, -rightVector.z);
	glm::vec3 downVector = glm::vec3(-upVector.x, -upVector.y, -upVector.z);
	glm::vec3 farTop = centerFar + (upVector * farHeight);
	glm::vec3 farBottom = centerFar + (downVector * farHeight);
	glm::vec3 nearTop = centerNear + (upVector * nearHeight);
	glm::vec3 nearBottom = centerNear + (downVector * nearHeight);
	std::vector<glm::vec4> points(8);
	points[0] = calculateLightSpaceFrustumCorner(farTop, rightVector, farWidth);
	points[1] = calculateLightSpaceFrustumCorner(farTop, leftVector, farWidth);
	points[2] = calculateLightSpaceFrustumCorner(farBottom, rightVector, farWidth);
	points[3] = calculateLightSpaceFrustumCorner(farBottom, leftVector, farWidth);
	points[4] = calculateLightSpaceFrustumCorner(nearTop, rightVector, nearWidth);
	points[5] = calculateLightSpaceFrustumCorner(nearTop, leftVector, nearWidth);
	points[6] = calculateLightSpaceFrustumCorner(nearBottom, rightVector, nearWidth);
	points[7] = calculateLightSpaceFrustumCorner(nearBottom, leftVector, nearWidth);
	return points;
}

glm::vec4 ShadowBox::calculateLightSpaceFrustumCorner(glm::vec3 startPoint, glm::vec3 direction, float width)
{
	glm::vec3 point = startPoint + (direction * width);
	glm::vec4 point4f = glm::vec4(point, 1.0f);
	return point4f;
}