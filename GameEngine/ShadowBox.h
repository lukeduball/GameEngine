#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

class ShadowBox
{
public:
	ShadowBox(glm::mat4 &lightViewMatrix);
	void update();
	glm::vec3 getCenter();
	float getWidth();
	float getHeight();
	float getLength();

	static const float SHADOW_DISTANCE;
private:
	static const glm::vec4 UP;
	static const glm::vec4 FORWARD;
	static const float OFFSET;
	float minX, maxX;
	float minY, maxY;
	float minZ, maxZ;
	glm::mat4 lightViewMatrix;
	float farWidth, farHeight, nearWidth, nearHeight;
	void calculateWidthsAndHeights();
	std::vector<glm::vec4> calculateFrustumVertices(glm::vec3 centerNear, glm::vec3 centerFar);
	glm::vec4 calculateLightSpaceFrustumCorner(glm::vec3 startPoint, glm::vec3 direction, float width);
};