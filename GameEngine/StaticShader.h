#pragma once

#include <vector>
#include "Shader.h"
#include "TerraForge.h"

class Light;

class StaticShader : public Shader
{
public:
	StaticShader();
	void loadTransformationMatrix(glm::mat4 matrix);
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadViewCameraMatrix(glm::mat4 matrix);
	void loadShineVariables(GLfloat damper, GLfloat reflectivity);
	void loadLights(std::vector<Light*> lights);
	void loadFakeLightingVariable(bool useFakeLighting);
	void loadSkyColor(glm::vec3 skyColor);
	void loadNumberOfRows(int numberOfRows);
	void loadOffset(glm::vec2 offset);
	void loadClipPlane(glm::vec4 plane);

protected:
	void getAllUniformLocations();

private:
	//MOVE TO TERRA FORGE
	static const int MAX_LIGHTS = 4;
	GLuint location_trasformationMatrix;
	GLuint location_projectionMatrix;
	GLuint location_cameraViewMatrix;
	GLuint location_lightPosition[MAX_LIGHTS];
	GLuint location_lightColor[MAX_LIGHTS];
	GLuint location_attenuation[MAX_LIGHTS];
	GLuint location_shineDamper;
	GLuint location_reflectivity;
	GLuint location_useFakeLighting;
	GLuint location_skyColor;
	GLuint location_numberOfRows;
	GLuint location_offset;
	GLuint location_plane;
};