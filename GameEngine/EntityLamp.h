#pragma once

#include "Entity.h"
#include "Light.h"

class EntityLamp : public Entity
{
public:
	EntityLamp(TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale, glm::vec3 lightColor, glm::vec3 attenuation);
	Light* getLight();

	void Update();

private:
	Light light;
};