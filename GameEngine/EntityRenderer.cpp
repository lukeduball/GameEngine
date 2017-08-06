#include "EntityRenderer.h"
#include "Maths.h"
#include "TerraForge.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

																//Last two are near and far clipping planes -- objects need to be between them to be drawn
EntityRenderer::EntityRenderer(StaticShader &shader, glm::mat4 projectionMatrix)
{
	this->shader = shader;
	shader.Use();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.Stop();
}


void EntityRenderer::render(std::vector<std::list<Entity*>> entitiesList)
{
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
				prepareTexturedModel(model);
				firstPrepare = false;
			}
			prepareInstance(entity);
			glDrawElements(GL_TRIANGLES, model->getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		unbindTexturedModel();
	}
}

void EntityRenderer::prepareInstance(Entity *entity)
{
	//Transform the object and passes the matrix to the shader
	glm::mat4 transformMatrix = Maths::createTransformationMatrix(entity->getPosition(), entity->getRotationX(), entity->getRotationY(), entity->getRotationZ(), entity->getScale());
	shader.loadTransformationMatrix(transformMatrix);
	shader.loadOffset(glm::vec2(entity->getTextureXOffset(), entity->getTextureYOffset()));
}


void EntityRenderer::prepareTexturedModel(TexturedModel *model)
{
	glBindVertexArray(model->getRawModel().getVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	shader.loadNumberOfRows(model->getTexture()->getNumberOfRows());
	if (model->getTexture()->hasTrasparency())
	{
		TerraForge::disableCulling();
	}
	shader.loadFakeLightingVariable(model->getTexture()->useFakeLighting());
	shader.loadShineVariables(model->getTexture()->getShineDamper(), model->getTexture()->getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, model->getTexture()->getID());
}

void EntityRenderer::unbindTexturedModel()
{
	TerraForge::enableCulling();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

//std::list<Entity> EntityRenderer::getEntityListFromModelID(int id)
//{
//	switch (id)
//	{
//	case 0:
//		return dragonEntities;
//	}
//}
//
//void EntityRenderer::processEntity(Entity entity)
//{
//	switch (entity.getModel().getID())
//	{
//	case 0:
//		dragonEntities.push_back(entity); break;
//	}
//}