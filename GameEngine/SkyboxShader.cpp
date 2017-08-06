#include "SkyboxShader.h"
#include "TerraForge.h"

const GLfloat SkyboxShader::ROTATION_SPEED = 0.01f;

SkyboxShader::SkyboxShader() : Shader("resources/shaders/skybox.vs", "resources/shaders/skybox.frag") 
{
	getAllUniformLocations();
}

void SkyboxShader::loadProjectionMatrix(glm::mat4 matrix)
{
	Shader::loadMatrix(location_projectionMatrix, matrix);
}

void SkyboxShader::loadViewCameraMatrix(glm::mat4 matrix)
{
	rotation += ROTATION_SPEED * TerraForge::deltaTime;
	matrix = glm::rotate(matrix, rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	Shader::loadMatrix(location_cameraViewMatrix, matrix);
}

void SkyboxShader::loadFogColor(glm::vec3 fog)
{
	Shader::loadVector(location_fogColor, fog);
}

void SkyboxShader::loadBlendFactor(GLfloat blend)
{
	Shader::loadFloat(location_blendFactor, blend);
}

void SkyboxShader::connectTextureUnits()
{
	Shader::loadInt(location_cubeMap, 0);
	Shader::loadInt(location_cubeMap2, 1);
}

void SkyboxShader::getAllUniformLocations()
{
	location_projectionMatrix = Shader::getUniformLocation("projectionMatrix");
	location_cameraViewMatrix = Shader::getUniformLocation("viewMatrix");
	location_fogColor = Shader::getUniformLocation("fogColor");
	location_cubeMap = Shader::getUniformLocation("cubeMap");
	location_cubeMap2 = Shader::getUniformLocation("cubeMap2");
	location_blendFactor = Shader::getUniformLocation("blendFactor");
}