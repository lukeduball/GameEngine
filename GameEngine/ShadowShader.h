#pragma once

#include "Shader.h"

class ShadowShader : public Shader
{
public:
	ShadowShader();
	void loadMvpMatrix(glm::mat4 matrix);
protected:
	void getAllUniformLocations();
private:
	GLuint location_mvpMatrix;
};