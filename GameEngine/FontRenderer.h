#pragma once

#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Loader.h"
#include "FontType.h"
#include "RawModel.h"
#include "FontShader.h"

class FontRenderer
{
public:
	FontRenderer(Loader loader);
	void setCurrentFont(std::string fontName);
	void renderString(std::string theString, float posX, float posY, glm::vec3 color);
	void renderCharacter(char c, float posX, float posY, float &moveX);
	void setFontSize(float size);

private:
	float textScale;
	FontShader shader;
	RawModel quad;
	FontType *currentFont;
	std::map<std::string, FontType> fontMap;
	void loadArial(Loader loader);
	void loadCandara(Loader loader);
};