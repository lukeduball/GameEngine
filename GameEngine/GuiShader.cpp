#include "GuiShader.h"

GuiShader::GuiShader() : Shader("resources/shaders/gui.vs", "resources/shaders/gui.frag")
{
	getAllUniformLocations();
}

void GuiShader::loadTransformationMatrix(glm::mat4 matrix)
{
	Shader::loadMatrix(location_transformationMatrix, matrix);
}

void GuiShader::getAllUniformLocations()
{
	this->location_transformationMatrix = Shader::getUniformLocation("transformationMatrix");
}