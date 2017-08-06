#include "TerrainRenderer.h"
#include "Maths.h"

TerrainRenderer::TerrainRenderer(TerrainShader &shader, glm::mat4 projectionMatrix)
{
	this->shader = shader;
	shader.Use();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.connectTextureUnits();
	shader.Stop();
}

void TerrainRenderer::render(std::list<Terrain> terrains)
{
	for (Terrain terrain : terrains)
	{
		prepareTerrainModel(&terrain);
		modelMatrix(&terrain);
		glDrawElements(GL_TRIANGLES, terrain.getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
		unbindTexturedModel();
	}
}

void TerrainRenderer::prepareTerrainModel(Terrain *terrain)
{
	glBindVertexArray(terrain->getModel().getVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	bindTextures(terrain);
	shader.loadShineVariables(1, 0);
}

void TerrainRenderer::bindTextures(Terrain *terrain)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, terrain->getTexturePack()->getBackgroundTexture().getID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, terrain->getTexturePack()->getRTexture().getID());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, terrain->getTexturePack()->getGTexture().getID());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, terrain->getTexturePack()->getBTexture().getID());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, terrain->getBlendMap()->getID());

}

void TerrainRenderer::modelMatrix(Terrain *terrain)
{
	glm::mat4 transformMatrix = Maths::createTransformationMatrix(glm::vec3(terrain->getX(), 0.0f, terrain->getZ()), 0.0f, 0.0f, 0.0f, 1.0f);
	shader.loadTransformationMatrix(transformMatrix);
}

void TerrainRenderer::unbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}