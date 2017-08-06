#pragma once

#include "ShadowDepthBuffer.h"
#include "ShadowShader.h"
#include "ShadowBox.h"
#include "Entity.h"
#include "Light.h"

#include <vector>
#include <list>

class ShadowRenderer
{
public:
	ShadowRenderer();
	void render(std::vector<std::list<Entity*>> entities, Light sun);
	ShadowDepthBuffer getDepthBuffer();
	glm::mat4 getToShadowMapSpaceMatrix();
	glm::mat4 getLightSpaceTransform();
private:
	ShadowBox shadowBox;
	ShadowDepthBuffer shadowFBO;
	ShadowShader shader;
	glm::mat4 projectionMatrix;
	glm::mat4 lightViewMatrix;
	glm::mat4 projectionViewMatrix;
	glm::mat4 offset;

	void prepare(glm::vec3 lightPosition);
	void finish();
	void prepareEntityInstance(Entity *entity);
	void bindEntityModel(RawModel model);
	void updateLightViewMatrix(glm::vec3 direction, glm::vec3 center);
	void updateOrthoProjectionMatrix(float width, float height, float length);
	glm::mat4 createOffset();
};

