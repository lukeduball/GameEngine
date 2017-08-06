#include "ShadowRenderer.h"
#include "TerraForge.h"
#include "MasterRenderer.h"
#include "Maths.h"
#include "ShadowBox.h"
#include <iostream>
#include <math.h>

#include <glm/gtx/string_cast.hpp>

ShadowRenderer::ShadowRenderer() : shadowFBO(ShadowDepthBuffer()), shader(ShadowShader()), shadowBox(ShadowBox(lightViewMatrix)), offset(createOffset()) {}

void ShadowRenderer::render(std::vector<std::list<Entity*>> entitiesList, Light sun)
{
	shadowBox.update();
	glm::vec3 sunPosition = sun.getPosition();
	glm::vec3 lightDirection = sunPosition * -1.0f;
	prepare(lightDirection);
	for (int i = 0; i < entitiesList.size(); i++)
	{
		std::list<Entity*> list = entitiesList[i];
		bool firstPrepare = true;
		TexturedModel *model = NULL;
		for (Entity *entity : list)
		{
			if (firstPrepare)
			{
				model = &entity->getModel();
				bindEntityModel(model->getRawModel());
				firstPrepare = false;
			}
			prepareEntityInstance(entity);
			glDrawElements(GL_TRIANGLES, model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		}
	}
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	finish();

}

ShadowDepthBuffer ShadowRenderer::getDepthBuffer()
{
	return shadowFBO;
}

glm::mat4 ShadowRenderer::getToShadowMapSpaceMatrix()
{
	return offset * projectionViewMatrix;
}

glm::mat4 ShadowRenderer::getLightSpaceTransform()
{
	return lightViewMatrix;
}

void ShadowRenderer::prepare(glm::vec3 lightDirection)
{
	updateOrthoProjectionMatrix(shadowBox.getWidth(), shadowBox.getHeight(), shadowBox.getLength());
	updateLightViewMatrix(lightDirection, shadowBox.getCenter());
	projectionViewMatrix = projectionMatrix * lightViewMatrix;
	shadowFBO.bindShadowBuffer();
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	shader.Use();
}

void ShadowRenderer::finish()
{
	shader.Stop();
	shadowFBO.unbindFrameBuffer();
}

void ShadowRenderer::prepareEntityInstance(Entity *entity)
{
	glm::mat4 modelMatrix = Maths::createTransformationMatrix(entity->getPosition(), entity->getRotationX(), entity->getRotationY(), entity->getRotationZ(), entity->getScale());
	glm::mat4 mvpMatrix = projectionViewMatrix * modelMatrix;
	shader.loadMvpMatrix(mvpMatrix);
	
}

void ShadowRenderer::bindEntityModel(RawModel model)
{
	glBindVertexArray(model.getVAOID());
	glEnableVertexAttribArray(0);
}

void ShadowRenderer::updateLightViewMatrix(glm::vec3 direction, glm::vec3 center)
{
	glm::normalize(direction);
	center = center * -1.0f;
	lightViewMatrix = glm::mat4();
	float pitch = acos(glm::length(glm::vec2(direction.x, direction.z)));
	lightViewMatrix = glm::rotate(lightViewMatrix, glm::degrees(pitch), glm::vec3(1, 0, 0));
	float yaw = glm::degrees(atan(direction.x / direction.z));
	yaw = direction.z > 0 ? yaw - 180 : yaw;
	lightViewMatrix = glm::rotate(lightViewMatrix, yaw, glm::vec3(0, 1, 0));
	lightViewMatrix = glm::translate(lightViewMatrix, center);
}

void ShadowRenderer::updateOrthoProjectionMatrix(float width, float height, float length)
{
	projectionMatrix = glm::mat4();
	projectionMatrix[0][0] = 2.0f / width;
	projectionMatrix[1][1] = 2.0f / height;
	projectionMatrix[2][2] = 2.0f / length;
	projectionMatrix[3][3] = 1;
}

glm::mat4 ShadowRenderer::createOffset()
{
	glm::mat4 offset = glm::mat4();
	offset = glm::translate(offset, glm::vec3(0.5f, 0.5f, 0.5f));
	offset = glm::scale(offset, glm::vec3(0.5f, 0.5f, 0.5f));
	return offset;
}

