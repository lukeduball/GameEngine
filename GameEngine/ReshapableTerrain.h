#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <list>

struct Line
{
	glm::vec3 point1;
	glm::vec3 point2;
};

class ReshapableTerrain
{
public:
	ReshapableTerrain();
	void triangleReshape(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);
	float distanceBetweenPoints(glm::vec3 point1, glm::vec3 point2);
	bool doLinesIntersect(glm::vec3 line1Point1, glm::vec3 line1Point2, glm::vec3 line2Point1, glm::vec3 line2Point2);
	bool doLinesIntersect(Line line1, Line line2);
	bool isPointBetweenRange(glm::vec3 point, Line line1, Line line2);
	void sortHighLowPoints(float &min, float &max, float rangeVal1, float rangeVal2);
	bool doesLineIntersectWithShapeBounds(std::vector<Line> shapeBounds, Line line);
	std::vector<glm::vec3> vertices;
private:
	std::vector<GLuint> indices;
	GLuint vbo;
};