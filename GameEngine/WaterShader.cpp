#include "WaterShader.h"

WaterShader::WaterShader() : Shader("resources/shaders/water.vs", "resources/shaders/water.frag") 
{
	getAllUniformLocations();
}

void WaterShader::loadProjectionMatrix(glm::mat4 matrix)
{
	Shader::loadMatrix(location_projectionMatrix, matrix);
}


void WaterShader::loadViewMatrix(glm::mat4 matrix)
{
	Shader::loadMatrix(location_viewMatrix, matrix);
}

void WaterShader::loadCameraPosition(glm::vec3 position)
{
	Shader::loadVector(location_cameraPosition, position);
}

void WaterShader::loadModelMatrix(glm::mat4 matrix)
{
	Shader::loadMatrix(location_modelMatrix, matrix);
}

void WaterShader::connectTextures()
{
	Shader::loadInt(location_reflectionTexture, 0);
	Shader::loadInt(location_refractionTexture, 1);
	Shader::loadInt(location_dudvMap, 2);
	Shader::loadInt(location_normalMap, 3);
	Shader::loadInt(location_depthMap, 4);
}

void WaterShader::loadMoveFactor(float factor)
{
	Shader::loadFloat(location_moveFactor, factor);
}

void WaterShader::loadLight(Light sun)
{
	Shader::loadVector(location_lightColor, sun.getColor());
	Shader::loadVector(location_lightColor, sun.getPosition());
}

void WaterShader::getAllUniformLocations()
{
	location_viewMatrix = Shader::getUniformLocation("viewMatrix");
	location_projectionMatrix = Shader::getUniformLocation("projectionMatrix");
	location_modelMatrix = Shader::getUniformLocation("modelMatrix");
	location_reflectionTexture = Shader::getUniformLocation("reflectionTexture");
	location_refractionTexture = Shader::getUniformLocation("refractionTexture");
	location_dudvMap = Shader::getUniformLocation("dudvMap");
	location_normalMap = Shader::getUniformLocation("normalMap");
	location_moveFactor = Shader::getUniformLocation("moveFactor");
	location_cameraPosition = Shader::getUniformLocation("cameraPosition");
	location_lightColor = Shader::getUniformLocation("lightColor");
	location_lightPosition = Shader::getUniformLocation("lightPosition");
	location_depthMap = Shader::getUniformLocation("depthMap");
}
