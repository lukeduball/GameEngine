#pragma once

#include "Shader.h"

class ParticleShader : public Shader
{
public:
	ParticleShader();
	void loadProjectionMatrix(glm::mat4 matrix);
	void loadNumberOfRows(float numb);

protected:
	void getAllUniformLocations();

private:
	GLuint location_projectionMatrix;
	GLuint location_numberOfRows;
};