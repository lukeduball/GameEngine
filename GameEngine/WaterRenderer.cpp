#include "WaterRenderer.h"
#include "Maths.h"
#include "TerraForge.h"
#include "Camera.h"

#include <vector>
#include <iostream>

const float WaterRenderer::WAVE_SPEED = 0.03f;

WaterRenderer::WaterRenderer(Loader loader, glm::mat4 projectionMatrix, WaterFrameBuffers &fbos) : quad(loader.loadToVAO(std::vector<GLfloat>{ -1, -1, -1, 1, 1, -1, 1, -1, -1, 1, 1, 1 }, 2)), shader(WaterShader()), fbos(fbos), dudvTexture(loader.loadTexture("resources/images/waterDUDV.png")), normalTexture(loader.loadTexture("resources/images/matchingNormalMap.png"))
{
	shader.Use();
	shader.connectTextures();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.Stop();
}


void WaterRenderer::render(std::list<WaterTile> water, Light sun)
{
	prepareRender(sun);
	for (WaterTile tile : water)
	{
		shader.loadModelMatrix(Maths::createTransformationMatrix(glm::vec3(tile.getX(), tile.getHeight(), tile.getZ()), 0.0f, 0.0f, 0.0f, WaterTile::TILE_SIZE));
		glDrawArrays(GL_TRIANGLES, 0, quad.getVertexCount());
	}
	finishRender();
}


void WaterRenderer::prepareRender(Light sun)
{
	shader.Use();
	shader.loadViewMatrix(TerraForge::camera.getViewMatrix());
	shader.loadCameraPosition(TerraForge::camera.getPosition());
	moveFactor += WAVE_SPEED * TerraForge::deltaTime;
	moveFactor = fmodf(moveFactor, 1.0f);
	shader.loadMoveFactor(moveFactor);
	shader.loadLight(sun);
	glBindVertexArray(quad.getVAOID());
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fbos.getReflectionTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, fbos.getRefractionTexture());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, dudvTexture);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, normalTexture);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, fbos.getRefractionDepthTexture());

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void WaterRenderer::finishRender()
{
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.Stop();
}
