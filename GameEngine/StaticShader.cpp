#include "StaticShader.h"
#include "Light.h"

#include <string>



StaticShader::StaticShader() : Shader("resources/shaders/generic.vs", "resources/shaders/generic.frag") 
{
	getAllUniformLocations();
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix)
{
	Shader::loadMatrix(location_trasformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix)
{
	Shader::loadMatrix(location_projectionMatrix, matrix);
}

void StaticShader::loadViewCameraMatrix(glm::mat4 matrix)
{
	Shader::loadMatrix(location_cameraViewMatrix, matrix);
}

void StaticShader::loadShineVariables(GLfloat damper, GLfloat reflectivity)
{
	Shader::loadFloat(location_shineDamper, damper);
	Shader::loadFloat(location_reflectivity, reflectivity);
}

void StaticShader::loadLights(std::vector<Light*> lights)
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

void StaticShader::loadFakeLightingVariable(bool useFakeLighting)
{
	Shader::loadBoolean(location_useFakeLighting, useFakeLighting);
}

void StaticShader::loadSkyColor(glm::vec3 skyColor)
{
	Shader::loadVector(location_skyColor, skyColor);
}

void StaticShader::loadNumberOfRows(int numberOfRows)
{
	Shader::loadFloat(location_numberOfRows, numberOfRows);
}

void StaticShader::loadOffset(glm::vec2 offset)
{
	Shader::loadVector2(location_offset, offset);
}

void StaticShader::loadClipPlane(glm::vec4 plane)
{
	Shader::loadVector4(location_plane, plane);
}

void StaticShader::getAllUniformLocations()
{
	this->location_trasformationMatrix = Shader::getUniformLocation("transformationMatrix");
	this->location_projectionMatrix = Shader::getUniformLocation("projection");
	this->location_cameraViewMatrix = Shader::getUniformLocation("view");
	this->location_shineDamper = Shader::getUniformLocation("shineDamper");
	this->location_reflectivity = Shader::getUniformLocation("reflectivity");
	this->location_useFakeLighting = Shader::getUniformLocation("useFakeLighting");
	this->location_skyColor = Shader::getUniformLocation("skyColor");
	this->location_numberOfRows = Shader::getUniformLocation("numberOfRows");
	this->location_offset = Shader::getUniformLocation("offset");
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