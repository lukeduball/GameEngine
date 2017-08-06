#include  "FontShader.h"

FontShader::FontShader() : Shader("resources/shaders/font.vs", "resources/shaders/font.frag")
{
	getAllUniformLocations();
}

void FontShader::loadColor(glm::vec3 color)
{
	Shader::loadVector(location_color, color);
}

void FontShader::loadTranslationMatrix(glm::mat4 vector)
{
	Shader::loadMatrix(location_translation, vector);
}

void FontShader::loadCharacterCoords(glm::vec4 coords)
{
	Shader::loadVector4(location_characterCoords, coords);
}

void FontShader::loadSmoothFactors(float width, float edge)
{
	Shader::loadFloat(location_smoothWidth, width);
	Shader::loadFloat(location_smoothEdge, edge);
}
void FontShader::loadBackData(float borderWidth, float borderEdge, glm::vec2 shadowOffset, glm::vec3 backColor)
{
	Shader::loadFloat(location_borderWidth, borderWidth);
	Shader::loadFloat(location_borderEdge, borderEdge);
	Shader::loadVector2(location_shadowOffset, shadowOffset);
	Shader::loadVector(location_backColor, backColor);
}



void FontShader::getAllUniformLocations()
{
	location_color = Shader::getUniformLocation("color");
	location_translation = Shader::getUniformLocation("translation");
	location_characterCoords = Shader::getUniformLocation("textureCoords");

	location_smoothWidth = Shader::getUniformLocation("width");
	location_smoothEdge = Shader::getUniformLocation("edge");
	
	location_borderWidth = Shader::getUniformLocation("borderWidth");
	location_borderEdge = Shader::getUniformLocation("borderEdge");
	location_shadowOffset = Shader::getUniformLocation("offset");
	location_backColor = Shader::getUniformLocation("outlineColor");
}

