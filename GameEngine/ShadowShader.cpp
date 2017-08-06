#include "ShadowShader.h"

ShadowShader::ShadowShader() : Shader("resources/shaders/shadow.vs", "resources/shaders/shadow.frag")
{
	getAllUniformLocations();
}

void ShadowShader::loadMvpMatrix(glm::mat4 matrix)
{
	Shader::loadMatrix(location_mvpMatrix, matrix);
}

void ShadowShader::getAllUniformLocations()
{
	location_mvpMatrix = Shader::getUniformLocation("mvpMatrix");
}
