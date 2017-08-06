#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Maths
{
public:
	static const double PI;
	static const float  PI_F;

	static glm::mat4 createTransformationMatrix(glm::vec3 position, float rotX, float rotY, float rotZ, float scale);
	static glm::mat4 createTransformationMatrix(glm::vec2 translation, glm::vec2 scale);
	static float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);
};