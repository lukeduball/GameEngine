#pragma once

#include "Shader.h"
#include "Light.h"

class WaterShader : public Shader
{
public:
	WaterShader();
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadViewMatrix(glm::mat4 matrix);
	void loadModelMatrix(glm::mat4 matrix);
	void connectTextures();
	void loadMoveFactor(float factor);
	void loadCameraPosition(glm::vec3 position);
	void loadLight(Light sun);
protected:
	void getAllUniformLocations();
private:
	GLuint location_viewMatrix;
	GLuint location_modelMatrix;
	GLuint location_projectionMatrix;
	GLuint location_reflectionTexture;
	GLuint location_refractionTexture;
	GLuint location_dudvMap;
	GLuint location_normalMap;
	GLuint location_moveFactor;
	GLuint location_cameraPosition;
	GLuint location_lightColor;
	GLuint location_lightPosition;
	GLuint location_depthMap;
};

