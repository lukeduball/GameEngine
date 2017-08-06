#pragma once

#include <string>
#include <map>

#define GLEW_STATIC
#include <GL/glew.h>

#include "Loader.h"

struct Character 
{
	int x, y;
	int width, height;
	int xOff, yOff;
	int xadvance;
};

class FontType
{
public:
	int textureDimension;
	FontType();
	FontType(std::string textureAtlas, Loader loader);
	GLuint getTexture();
	std::map<int, Character> getCharacterMap();
	void loadCharacter(char c, int x, int y, int width, int height, int xOff, int yOff);

private:
	void loadFontFile(const GLchar *fileName);
	GLuint textureID;
	std::map<int, Character> characterMap;
};