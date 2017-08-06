#pragma once

#include "Shader.h"

class FontShader : public Shader 
{
public:
	FontShader();
	void loadColor(glm::vec3 color);
	void loadTranslationMatrix(glm::mat4 matrix);
	void loadCharacterCoords(glm::vec4 coords);
	void loadSmoothFactors(float width, float edge);
	void loadBackData(float borderWidth, float borderEdge, glm::vec2 shadowOffset, glm::vec3 backColor);

protected:
	void getAllUniformLocations();

private:
	GLuint location_color;
	GLuint location_translation;
	GLuint location_characterCoords;

	GLuint location_smoothWidth;
	GLuint location_smoothEdge;

	GLuint location_borderWidth;
	GLuint location_borderEdge;
	GLuint location_shadowOffset;
	GLuint location_backColor;

};