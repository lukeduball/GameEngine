#include "Maths.h"

const double Maths::PI = 3.141592653589793238463;
const float  Maths::PI_F = 3.14159265358979f;

glm::mat4 Maths::createTransformationMatrix(glm::vec3 position, float rotX, float rotY, float rotZ, float scale)
{
	glm::mat4 matrix = glm::mat4();
	matrix = glm::translate(matrix, position);
	matrix = glm::rotate(matrix, rotX, glm::vec3(1.0f, 0.0f, 0.0f));
	matrix = glm::rotate(matrix, rotY, glm::vec3(0.0f, 1.0f, 0.0f));
	matrix = glm::rotate(matrix, rotZ, glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::scale(matrix, glm::vec3(scale));
	return matrix;
}

glm::mat4 Maths::createTransformationMatrix(glm::vec2 translation, glm::vec2 scale)
{
	glm::mat4 matrix = glm::mat4();
	matrix = glm::translate(matrix, glm::vec3(translation.x, translation.y, 0.0f));
	matrix = glm::scale(matrix, glm::vec3(scale.x, scale.y, 0.0f));
	return matrix;

}

float Maths::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) 
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}