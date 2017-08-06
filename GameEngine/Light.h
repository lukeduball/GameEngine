#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light 
{
public:
	Light(glm::vec3 position, glm::vec3 color);
	Light(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation);

	glm::vec3 getPosition();

	void setPosition(glm::vec3 pos);

	glm::vec3 getColor();

	void setColor(glm::vec3 col);

	glm::vec3 getAttenuation();
	void setAttenuation(glm::vec3 atten);

private:
	glm::vec3 position;
	glm::vec3 color;
	//How distance from light affects objects
	glm::vec3 attenuation;
};