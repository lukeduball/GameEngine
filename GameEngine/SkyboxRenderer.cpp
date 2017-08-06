#include "SkyboxRenderer.h"
#include "TerraForge.h"

SkyboxRenderer::SkyboxRenderer(Loader loader, glm::mat4 projectionMatrix) : cube(loader.loadToVAO(std::vector<GLfloat>{ -500.0f, 500.0f, -500.0f,
	-500.0f, -500.0f, -500.0f,
	500.0f, -500.0f, -500.0f,
	500.0f, -500.0f, -500.0f,
	500.0f, 500.0f, -500.0f,
	-500.0f, 500.0f, -500.0f,

	-500.0f, -500.0f, 500.0f,
	-500.0f, -500.0f, -500.0f,
	-500.0f, 500.0f, -500.0f,
	-500.0f, 500.0f, -500.0f,
	-500.0f, 500.0f, 500.0f,
	-500.0f, -500.0f, 500.0f,

	500.0f, -500.0f, -500.0f,
	500.0f, -500.0f, 500.0f,
	500.0f, 500.0f, 500.0f,
	500.0f, 500.0f, 500.0f,
	500.0f, 500.0f, -500.0f,
	500.0f, -500.0f, -500.0f,

	-500.0f, -500.0f, 500.0f,
	-500.0f, 500.0f, 500.0f,
	500.0f, 500.0f, 500.0f,
	500.0f, 500.0f, 500.0f,
	500.0f, -500.0f, 500.0f,
	-500.0f, -500.0f, 500.0f,

	-500.0f, 500.0f, -500.0f,
	500.0f, 500.0f, -500.0f,
	500.0f, 500.0f, 500.0f,
	500.0f, 500.0f, 500.0f,
	-500.0f, 500.0f, 500.0f,
	-500.0f, 500.0f, -500.0f,

	-500.0f, -500.0f, -500.0f,
	-500.0f, -500.0f, 500.0f,
	500.0f, -500.0f, -500.0f,
	500.0f, -500.0f, -500.0f,
	-500.0f, -500.0f, 500.0f,
	500.0f, -500.0f, 500.0f }, 3)), texture(loader.loadCubeMap(TerraForge::skyboxPaths)), nightTexture(loader.loadCubeMap(TerraForge::nightBoxPaths)), shader(SkyboxShader())
{
	shader.Use();
	shader.connectTextureUnits();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.Stop();
}

void SkyboxRenderer::render(Camera &camera, glm::vec3 fogColor)
{
	shader.Use();
	glm::mat4 matrix = glm::mat4(glm::mat3(camera.getViewMatrix()));
	shader.loadViewCameraMatrix(matrix);
	shader.loadFogColor(fogColor);
	glBindVertexArray(cube.getVAOID());
	glEnableVertexAttribArray(0);
	bindTextures();
	glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.Stop();
}

void SkyboxRenderer::bindTextures()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, nightTexture);
	//Here and in master renderer create day/night system.
	shader.loadBlendFactor(0.0f);
}