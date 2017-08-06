#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <list>
#include <vector>

#include "Entity.h"
#include "StaticShader.h"

class EntityRenderer
{
public:
	EntityRenderer(StaticShader &shader, glm::mat4 projectionMatrix);

	void render(std::vector<std::list<Entity*>> entitiesList);

private:
	StaticShader shader;

	void prepareTexturedModel(TexturedModel *model);

	void prepareInstance(Entity *entity);

	void unbindTexturedModel();
};