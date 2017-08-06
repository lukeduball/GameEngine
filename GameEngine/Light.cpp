#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color) : Light(position, color, glm::vec3(1, 0, 0)) {}
Light::Light(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation) : position(position), color(color), attenuation(attenuation) {}

glm::vec3 Light::getPosition()
{
	return this->position;
}

void Light::setPosition(glm::vec3 pos)
{
	this->position = pos;
}

glm::vec3 Light::getColor()
{
	return this->color;
}

void Light::setColor(glm::vec3 col)
{
	this->color = col;
}

glm::vec3 Light::getAttenuation()
{
	return this->attenuation;
}

void Light::setAttenuation(glm::vec3 atten)
{
	this->attenuation = atten;
}