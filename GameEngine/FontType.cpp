#include "FontType.h"

#include <iostream>
#include <sstream>
#include <fstream>

FontType::FontType() {}

FontType::FontType(std::string textureAtlas, Loader loader)
{
	std::string path = std::string("resources/fonts/").append(textureAtlas).append(".fnt");
	//loadFontFile(path.c_str());
	std::string texturePath = std::string("resources/fonts/").append(textureAtlas).append(".png");
	textureID = loader.loadTexture(texturePath.c_str());
}

GLuint FontType::getTexture()
{
	return this->textureID;
}

std::map<int, Character> FontType::getCharacterMap()
{
	return this->characterMap;
}

void FontType::loadFontFile(const GLchar *fileName)
{
	std::string fileContents;
	std::ifstream fontFile;
	try
	{
		fontFile.open(fileName);
		std::stringstream fontStream;
		fontStream << fontFile.rdbuf();
		fontFile.close();
		fileContents = fontStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR LOADING THE FONT: " << fileName << std::endl;
	}

	try
	{
		int widthIndex = fileContents.find("scaleW=") + 7;
		this->textureDimension = stoi(fileContents.substr(widthIndex, fileContents.find("\n", widthIndex) - widthIndex));
		//int heightIndex = fileContents.find("scaleH=") + 7;
		//int imageHeight = stoi(fileContents.substr(heightIndex, fileContents.find("\n", heightIndex) - heightIndex));

		int padding[4];
		int paddingIndex = fileContents.find("padding=") + 8;
		for (int i = 0; i < 4; i++)
		{
			padding[i] = stoi(fileContents.substr(paddingIndex + i * 2, 1));
		}

		int charCountIndex = fileContents.find("chars count=") + 12;
		int charCount = stoi(fileContents.substr(charCountIndex, fileContents.find("\n", charCountIndex) - charCountIndex));
		int charIndex = fileContents.find("char id=");
		for (int i = 0; i < charCount; i++)
		{
			Character fontChar;
			int charBuff = charIndex + 111 * i;
			int charID = stoi(fileContents.substr(charBuff + 8, fileContents.find(" ", charBuff + 8) - charBuff + 8));
			int x = stoi(fileContents.substr(charBuff + 18, fileContents.find(" ", charBuff + 18) - charBuff + 18));
			fontChar.x = x;
			int y = stoi(fileContents.substr(charBuff + 25, fileContents.find(" ", charBuff + 25) - charBuff + 25));
			fontChar.y = y;
			int width = stoi(fileContents.substr(charBuff + 36, fileContents.find(" ", charBuff + 36) - charBuff + 36));
			fontChar.width = width;
			int height = stoi(fileContents.substr(charBuff + 48, fileContents.find(" ", charBuff + 48) - charBuff + 48));
			fontChar.height = height;
			int xOff = stoi(fileContents.substr(charBuff + 61, fileContents.find(" ", charBuff + 61) - charBuff + 61));
			fontChar.xOff = xOff;
			int yOff = stoi(fileContents.substr(charBuff + 74, fileContents.find(" ", charBuff + 74) - charBuff + 74));
			fontChar.yOff = yOff;
			int xadvance = stoi(fileContents.substr(charBuff + 88, fileContents.find(" ", charBuff + 88) - charBuff + 88));
			fontChar.xadvance = xadvance;
			characterMap[charID] = fontChar;
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR PROCESSING THE FONT FILE" << std::endl;
	}
}

void FontType::loadCharacter(char c, int x, int y, int width, int height, int xOff, int yOff)
{
	Character charData;
	charData.x = x;
	charData.y = y;
	charData.width = width;
	charData.height = height;
	charData.xOff = xOff;
	charData.yOff = yOff;
	characterMap[c] = charData;
}