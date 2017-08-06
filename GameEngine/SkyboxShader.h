#pragma once

#include "Shader.h"

class SkyboxShader : public Shader
{
public:
	SkyboxShader();
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadViewCameraMatrix(glm::mat4 matrix);
	void loadFogColor(glm::vec3 fog);
	void loadBlendFactor(GLfloat blend);
	void connectTextureUnits();

protected:
	void getAllUniformLocations();

private:
	GLuint location_projectionMatrix;
	GLuint location_cameraViewMatrix;
	GLuint location_fogColor;
	GLuint location_cubeMap;
	GLuint location_cubeMap2;
	GLuint location_blendFactor;
	static const GLfloat ROTATION_SPEED;
	GLfloat rotation = 0.0f;
};