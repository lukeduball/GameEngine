#pragma once

#include <vector>
#include "Shader.h"
#include "TerraForge.h"

class Light;

class TerrainShader : public Shader
{
public:
	TerrainShader();
	void loadTransformationMatrix(glm::mat4 matrix);
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadViewCameraMatrix(glm::mat4 matrix);
	void loadShineVariables(GLfloat damper, GLfloat reflectivity);
	void loadClipPlane(glm::vec4 plane);
	void loadLights(std::vector<Light*> light);
	void loadSkyColor(glm::vec3 skyColor);
	void connectTextureUnits();

protected:
	void getAllUniformLocations();

private:
	static const int MAX_LIGHTS = 4;
	GLuint location_trasformationMatrix;
	GLuint location_projectionMatrix;
	GLuint location_cameraViewMatrix;
	GLuint location_lightPosition[MAX_LIGHTS];
	GLuint location_lightColor[MAX_LIGHTS];
	GLuint location_attenuation[MAX_LIGHTS];
	GLuint location_shineDamper;
	GLuint location_reflectivity;
	GLuint location_skyColor;
	GLuint location_backgroundTexture;
	GLuint location_rTexture;
	GLuint location_gTexture;
	GLuint location_bTexture;
	GLuint location_blendMapTexture;
	GLuint location_plane;
};