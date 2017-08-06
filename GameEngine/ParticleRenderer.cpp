#include "ParticleRenderer.h"

#include "TerraForge.h"
#include "Camera.h"
#include "Particle.h"

#include <vector>
#include <iterator>
#include <iostream>

ParticleRenderer::ParticleRenderer(Loader &loader, glm::mat4 projection) : loader(loader), shader(ParticleShader()), quad(loader.loadToVAO(std::vector<GLfloat>{-0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f}, 2)), vbo(loader.createEmptyVBO(INSTANCE_DATA_LENGTH * MAX_INSTANCES))
{
	loader.addInstanceAttibute(quad.getVAOID(), vbo, 1, 4, INSTANCE_DATA_LENGTH, 0);
	loader.addInstanceAttibute(quad.getVAOID(), vbo, 2, 4, INSTANCE_DATA_LENGTH, 4);
	loader.addInstanceAttibute(quad.getVAOID(), vbo, 3, 4, INSTANCE_DATA_LENGTH, 8);
	loader.addInstanceAttibute(quad.getVAOID(), vbo, 4, 4, INSTANCE_DATA_LENGTH, 12);
	loader.addInstanceAttibute(quad.getVAOID(), vbo, 5, 4, INSTANCE_DATA_LENGTH, 16);
	loader.addInstanceAttibute(quad.getVAOID(), vbo, 6, 1, INSTANCE_DATA_LENGTH, 20);
	shader.Use();
	shader.loadProjectionMatrix(projection);
	shader.Stop();
}

void ParticleRenderer::render(glm::vec4 clipPlane)
{
	glm::mat4 viewMatrix = TerraForge::camera.getViewMatrix();
	prepare();
	for (int i = 0; i < ParticleTexture::nextParticle; i++)
	{
		pointer = 0;
		std::vector<GLfloat> vboData = std::vector<GLfloat>(particlesMap[i].size() * INSTANCE_DATA_LENGTH);
		bool firstRender = true;
		for (Particle *particle : particlesMap[i])
		{
			if (firstRender)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, particle->getTexture().getTexture());
				firstRender = false;
			}
			//Instanced setup
			updateModelViewMatrix(particle->getPosition(), particle->getRotation(), particle->getScale(), viewMatrix, vboData);
			vboData[pointer++] = particle->getIndex1().x;
			vboData[pointer++] = particle->getIndex1().y;
			vboData[pointer++] = particle->getIndex2().x;
			vboData[pointer++] = particle->getIndex2().y;
			vboData[pointer++] = particle->getBlendFactor();
			shader.loadNumberOfRows(particle->getTexture().getNumberOfRows());
		}
		loader.updateVBO(vbo, vboData);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, quad.getVertexCount(), particlesMap[i].size());
	}
	finishRendering();
}

void ParticleRenderer::updateModelViewMatrix(glm::vec3 position, float rotation, float scale, glm::mat4 viewMatrix, std::vector<GLfloat> &vboData)
{
	glm::mat4 modelMatrix = glm::mat4();
	modelMatrix = glm::translate(modelMatrix, glm::vec3(position));
	//transposes the modelMatrix's rotation matrix to cancel out with the viewMatrix
	modelMatrix[0][0] = viewMatrix[0][0];
	modelMatrix[0][1] = viewMatrix[1][0];
	modelMatrix[0][2] = viewMatrix[2][0];
	modelMatrix[1][0] = viewMatrix[0][1];
	modelMatrix[1][1] = viewMatrix[1][1];
	modelMatrix[1][2] = viewMatrix[2][1];
	modelMatrix[2][0] = viewMatrix[0][2];
	modelMatrix[2][1] = viewMatrix[1][2];
	modelMatrix[2][2] = viewMatrix[2][2];
	modelMatrix = glm::rotate(modelMatrix, rotation, glm::vec3(0, 0, 1));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
	glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
	storeMatrixData(modelViewMatrix, vboData);
}

void ParticleRenderer::storeMatrixData(glm::mat4 matrix, std::vector<GLfloat> &vboData)
{
	vboData[pointer++] = matrix[0][0];
	vboData[pointer++] = matrix[0][1];
	vboData[pointer++] = matrix[0][2];
	vboData[pointer++] = matrix[0][3];
	vboData[pointer++] = matrix[1][0];
	vboData[pointer++] = matrix[1][1];
	vboData[pointer++] = matrix[1][2];
	vboData[pointer++] = matrix[1][3];
	vboData[pointer++] = matrix[2][0];
	vboData[pointer++] = matrix[2][1];
	vboData[pointer++] = matrix[2][2];
	vboData[pointer++] = matrix[2][3];
	vboData[pointer++] = matrix[3][0];
	vboData[pointer++] = matrix[3][1];
	vboData[pointer++] = matrix[3][2];
	vboData[pointer++] = matrix[3][3];
}


void ParticleRenderer::cleanUp()
{
	for (int i = 0; i < ParticleTexture::nextParticle; i++)
	{
		for (Particle *particle : particlesMap[i])
		{
			delete particle;
		}
	}
}

void ParticleRenderer::prepare()
{
	shader.Use();
	glBindVertexArray(quad.getVAOID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(false);
}

void ParticleRenderer::finishRendering()
{
	glDepthMask(true);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glDisableVertexAttribArray(6);
	glBindVertexArray(0);
	shader.Stop();
}

void ParticleRenderer::update()
{
	for (int i = 0; i < ParticleTexture::nextParticle; i++)
	{
		std::list<Particle*>::iterator itr;
		for (itr = particlesMap[i].begin(); itr != particlesMap[i].end();)
		{
			Particle *particle = *itr;
			bool stillAlive = particle->update();
			if (!stillAlive)
			{
				itr = particlesMap[i].erase(itr);
				delete particle;
			}
			else
			{
				++itr;
			}
		}
	}

}

void ParticleRenderer::addParticle(Particle *particle)
{
	particlesMap[particle->getTexture().particleID].push_back(particle);
}