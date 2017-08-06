#include "EntityLamp.h"

EntityLamp::EntityLamp(TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, glm::vec3 lightColor, glm::vec3 attenuation) : Entity(model, position, rotX, rotY, rotZ, scale), light(Light(glm::vec3(this->position.x, this->position.y + 12.5f * scale, this->position.z), lightColor, attenuation)) {}

Light* EntityLamp::getLight()
{
	return &this->light;
}

void EntityLamp::Update()
{
	light.setPosition(glm::vec3(position.x, position.y + 12.5f * getScale(), position.z));
}