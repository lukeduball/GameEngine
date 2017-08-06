#pragma once

#include "Shader.h"

class GuiShader : public Shader
{
public:
	GuiShader();
	void loadTransformationMatrix(glm::mat4 matrix);
protected:
	void getAllUniformLocations();
private:
	GLuint location_transformationMatrix;
};