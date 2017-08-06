#include "ParticleShader.h"

ParticleShader::ParticleShader() : Shader("resources/shaders/particle.vs", "resources/shaders/particle.frag")
{
	getAllUniformLocations();
}

void ParticleShader::loadProjectionMatrix(glm::mat4 matrix)
{
	Shader::loadMatrix(location_projectionMatrix, matrix);
}

void ParticleShader::loadNumberOfRows(float numb)
{
	Shader::loadFloat(location_numberOfRows, numb);
}

void ParticleShader::getAllUniformLocations()
{
	location_projectionMatrix = Shader::getUniformLocation("projectionMatrix");
	location_numberOfRows = Shader::getUniformLocation("numberOfRows");
}
