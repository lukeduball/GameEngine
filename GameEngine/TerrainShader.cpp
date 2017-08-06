#include "TerrainShader.h"
#include "Light.h"



TerrainShader::TerrainShader() : Shader("resources/shaders/terrain.vs", "resources/shaders/terrain.frag")
{
	getAllUniformLocations();
}

void TerrainShader::loadTransformationMatrix(glm::mat4 matrix)
{
	Shader::loadMatrix(location_trasformationMatrix, matrix);
}

void TerrainShader::loadProjectionMatrix(glm::mat4 matrix)
{
	Shader::loadMatrix(location_projectionMatrix, matrix);
}

void TerrainShader::loadViewCameraMatrix(glm::mat4 matrix)
{
	Shader::loadMatrix(location_cameraViewMatrix, matrix);
}

void TerrainShader::loadShineVariables(GLfloat damper, GLfloat reflectivity)
{
	Shader::loadFloat(location_shineDamper, damper);
	Shader::loadFloat(location_reflectivity, reflectivity);
}

void TerrainShader::loadClipPlane(glm::vec4 plane)
{
	Shader::loadVector4(location_plane, plane);
}

void TerrainShader::loadLights(std::vector<Light*> lights)
{
	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		if (i < lights.size())
		{
			Shader::loadVector(location_lightPosition[i], lights[i]->getPosition());
			Shader::loadVector(location_lightColor[i], lights[i]->getColor());
			Shader::loadVector(location_attenuation[i], lights[i]->getAttenuation());
		}
		else
		{
			Shader::loadVector(location_lightPosition[i], glm::vec3(0, 0, 0));
			Shader::loadVector(location_lightColor[i], glm::vec3(0, 0, 0));
			Shader::loadVector(location_attenuation[i], glm::vec3(1, 0, 0));
		}
	}
}

void TerrainShader::loadSkyColor(glm::vec3 skyColor)
{
	Shader::loadVector(location_skyColor, skyColor);
}

void TerrainShader::connectTextureUnits()
{
	Shader::loadInt(location_backgroundTexture, 0);
	Shader::loadInt(location_rTexture, 1);
	Shader::loadInt(location_gTexture, 2);
	Shader::loadInt(location_bTexture, 3);
	Shader::loadInt(location_blendMapTexture, 4);
}

void TerrainShader::getAllUniformLocations()
{
	this->location_trasformationMatrix = Shader::getUniformLocation("transformationMatrix");
	this->location_projectionMatrix = Shader::getUniformLocation("projection");
	this->location_cameraViewMatrix = Shader::getUniformLocation("view");
	this->location_shineDamper = Shader::getUniformLocation("shineDamper");
	this->location_reflectivity = Shader::getUniformLocation("reflectivity");
	this->location_skyColor = Shader::getUniformLocation("skyColor");
	this->location_backgroundTexture = Shader::getUniformLocation("backgroundTexture");
	this->location_rTexture = Shader::getUniformLocation("rTexture");
	this->location_gTexture = Shader::getUniformLocation("gTexture");
	this->location_bTexture = Shader::getUniformLocation("bTexture");
	this->location_blendMapTexture = Shader::getUniformLocation("blendMap");
	this->location_plane = Shader::getUniformLocation("plane");

	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		std::string str = std::string("lightPosition[").append(std::to_string(i));
		location_lightPosition[i] = Shader::getUniformLocation(str.append("]").c_str());
		std::string str1 = std::string("lightColor[").append(std::to_string(i));
		location_lightColor[i] = Shader::getUniformLocation(str1.append("]").c_str());
		std::string str2 = std::string("attenuation[").append(std::to_string(i));
		location_attenuation[i] = Shader::getUniformLocation(str2.append("]").c_str());
	}
}
