#include "FontRenderer.h"
#include "Maths.h"
#include "TerraForge.h"

#include <iostream>

FontRenderer::FontRenderer(Loader loader) : quad(loader.loadToVAO(std::vector<GLfloat>{ -1, 1, -1, -1, 1, 1, 1, -1 }, 2)), shader(FontShader()), textScale(0.001f)
{
	loadArial(loader);
	loadCandara(loader);
	setCurrentFont("candara");
}

void FontRenderer::setCurrentFont(std::string fontName)
{
	currentFont = &fontMap[fontName];
}

void FontRenderer::setFontSize(float size)
{
	this->textScale = 0.0004f + 0.00001f * size;
}

void FontRenderer::renderString(std::string theString, float posX, float posY, glm::vec3 color)
{
	shader.Use();
	glBindVertexArray(quad.getVAOID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	if (TerraForge::freeCamera)
	{
		glDisable(GL_BLEND);
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	shader.loadColor(color);
	float edge = 0.1f /  (textScale / 0.001f);
	shader.loadSmoothFactors(0.46f, edge);
	shader.loadBackData(0.5f, edge, glm::vec2(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	//shader.loadBackData(0.45f, 0.1f, glm::vec2(0.006f), glm::vec3(1.0f, 1.0f, 1.0f));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, currentFont->getTexture());

	int stringLength = theString.length();
	const char* stringArray = theString.c_str();
	float moveX = 0;
	for (int i = 0; i < stringLength; i++)
	{
		if (stringArray[i] != ' ')
		{
			renderCharacter(stringArray[i], posX, posY, moveX);
		}
		else
		{
			moveX += 40 * textScale;
		}
	}


	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.Stop();
}

void FontRenderer::renderCharacter(char c, float posX, float posY, float &moveX)
{
	Character charData = currentFont->getCharacterMap()[c];
	float texX = (float)(charData.x) / (float)currentFont->textureDimension;
	float texY = (float)(charData.y) / (float)currentFont->textureDimension;
	shader.loadCharacterCoords(glm::vec4(texX, texY, texX + (float)charData.width / (float)currentFont->textureDimension, texY + (float)charData.height / (float)currentFont->textureDimension));

	float scaleX = (float)charData.width * textScale;
	float scaleY = (float)charData.height * textScale;
	//Moves the left side of the rectangle to line up with the origin position
	float offsetX = charData.width * textScale;
	//Moves bottom of the rectangle up to the origin position of the rectangle
	float offsetY = (charData.height - charData.yOff) * textScale;
	glm::mat4 translationMatrix = Maths::createTransformationMatrix(glm::vec2(posX + moveX + offsetX, posY + offsetY), glm::vec2(scaleX, scaleY));
	shader.loadTranslationMatrix(translationMatrix);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.getVertexCount());

	//Add value that each font decides how much to make the gap between letters
	moveX += ((charData.width-8) * 2.0f) * textScale;
}

void FontRenderer::loadArial(Loader loader)
{
	FontType arial = FontType("arial", loader);
	arial.textureDimension = 512;
	arial.loadCharacter('a', 407, 350, 38, 44, 0, 0);
	arial.loadCharacter('b', 374, 87, 37, 59, 0, 0);
	arial.loadCharacter('c', 452, 350, 37, 44, 0, 0);
	arial.loadCharacter('d', 418, 87, 36, 59, 0, 0);
	arial.loadCharacter('e', 3, 415, 39, 44, 0, 0);
	arial.loadCharacter('f', 462, 87, 24, 59, 0, 0);
	arial.loadCharacter('g', 117, 87, 37, 60, 0, 45);
	arial.loadCharacter('h', 464, 220, 35, 58, 0, 0);
	arial.loadCharacter('i', 428, 285, 8, 58, 0, 0);
	arial.loadCharacter('j', 157, 4, 16, 75, 0, 60);
	arial.loadCharacter('k', 443, 285, 35, 58, 0, 0);
	arial.loadCharacter('l', 483, 285, 7, 58, 0, 0);
	arial.loadCharacter('m', 137, 415, 57, 43, 0, 0);
	arial.loadCharacter('n', 200, 415, 35, 43, 0, 0);
	arial.loadCharacter('o', 49, 415, 39, 44, 0, 0);
	arial.loadCharacter('p', 3, 154, 37, 59, 0, 34);
	arial.loadCharacter('q', 47, 154, 36, 59, 0, 34);
	arial.loadCharacter('r', 240, 415, 23, 43, 0, 0);
	arial.loadCharacter('s', 95, 415, 34, 44, 0, 0);
	arial.loadCharacter('t', 228, 350, 21, 57, 0, 0);
	arial.loadCharacter('u', 269, 415, 34, 43, 0, 0);
	arial.loadCharacter('v', 310, 415, 38, 42, 0, 0);
	arial.loadCharacter('w', 356, 415, 58, 42, 0, 0);
	arial.loadCharacter('x', 420, 415, 39, 42, 0, 0);
	arial.loadCharacter('y', 92, 154, 38, 59, 0, 44);
	arial.loadCharacter('z', 467, 415, 37, 42, 0, 0);

	arial.loadCharacter('A', 403, 154, 54, 58, 0, 0);
	arial.loadCharacter('B', 463, 154, 44, 58, 0, 0);
	arial.loadCharacter('C', 384, 4, 51, 60, 0, 0);
	arial.loadCharacter('D', 2, 220, 48, 58, 0, 0);
	arial.loadCharacter('E', 57, 220, 44, 58, 0, 0);
	arial.loadCharacter('F', 108, 220, 39, 58, 0, 0);
	arial.loadCharacter('G', 441, 4, 54, 60, 0, 0);
	arial.loadCharacter('H', 152, 220, 46, 58, 0, 0);
	arial.loadCharacter('I', 495, 87, 8, 58, 0, 0);
	arial.loadCharacter('J', 283, 87, 32, 59, 0, 0);
	arial.loadCharacter('K', 204, 220, 48, 58, 0, 0);
	arial.loadCharacter('L', 258, 220, 36, 58, 0, 0);
	arial.loadCharacter('M', 301, 220, 55, 58, 0, 0);
	arial.loadCharacter('N', 362, 220, 46, 58, 0, 0);
	arial.loadCharacter('O', 3, 87, 55, 60, 0, 0);
	arial.loadCharacter('P', 414, 220, 45, 58, 0, 0);
	arial.loadCharacter('Q', 322, 4, 57, 63, 0, 5);
	arial.loadCharacter('R', 2, 285, 51, 58, 0, 0);
	arial.loadCharacter('S', 65, 87, 46, 60, 0, 0);
	arial.loadCharacter('T', 59, 285, 46, 58, 0, 0);
	arial.loadCharacter('U', 321, 87, 46, 59, 0, 0);
	arial.loadCharacter('V', 114, 285, 52, 58, 0, 0);
	arial.loadCharacter('W', 175, 285, 74, 58, 0, 0);
	arial.loadCharacter('X', 261, 285, 52, 58, 0, 0);
	arial.loadCharacter('Y', 319, 285, 52, 58, 0, 0);
	arial.loadCharacter('Z', 377, 285, 46, 58, 0, 0);

	arial.loadCharacter('0', 312, 154, 38, 59, 0, 0);
	arial.loadCharacter('1', 3, 350, 21, 58, 0, 0);
	arial.loadCharacter('2', 31, 350, 39, 58, 0, 0);
	arial.loadCharacter('3', 134, 154, 38, 59, 0, 0);
	arial.loadCharacter('4', 255, 349, 40, 58, 0, 0);
	arial.loadCharacter('5', 75, 350, 39, 58, 0, 0);
	arial.loadCharacter('6', 180, 154, 38, 59, 0, 0);
	arial.loadCharacter('7', 302, 350, 37, 57, 0, 0);
	arial.loadCharacter('8', 224, 154, 39, 59, 0, 0);
	arial.loadCharacter('9', 268, 154, 39, 59, 0, 0);
	fontMap["arial"] = arial;
}

void FontRenderer::loadCandara(Loader loader)
{
	FontType candara = FontType("candara", loader);
	candara.textureDimension = 512;
	candara.loadCharacter('a', 171, 384, 40, 46, 0, 0);
	candara.loadCharacter('b', 377, 81, 44, 61, 0, 0);
	candara.loadCharacter('c', 131, 384, 39, 47, 0, 0);
	candara.loadCharacter('d', 175, 83, 42, 59, 0, 0);
	candara.loadCharacter('e', 88, 384, 41, 46, 0, 0);
	candara.loadCharacter('f', 138, 84, 34, 57, 0, 0);
	candara.loadCharacter('g', 0, 82, 46, 65, 0, 45);
	candara.loadCharacter('h', 135, 147, 42, 60, 0, 0);
	candara.loadCharacter('i', 280, 147, 25, 60, 0, 0);
	candara.loadCharacter('j', 307, 2, 24, 69, 0, 60);
	candara.loadCharacter('k', 92, 149, 40, 57, 0, 0);
	candara.loadCharacter('l', 469, 269, 19, 54, 0, 0);
	candara.loadCharacter('m', 339, 384, 60, 46, 0, 0);
	candara.loadCharacter('n', 294, 384, 42, 46, 0, 0);
	candara.loadCharacter('o', 40, 383, 45, 48, 0, 0);
	candara.loadCharacter('p', 306, 81, 45, 62, 0, 34);
	candara.loadCharacter('q', 260, 81, 45, 62, 0, 34);
	candara.loadCharacter('r', 259, 386, 32, 42, 0, 0);
	candara.loadCharacter('s', 1, 384, 36, 46, 0, 0);
	candara.loadCharacter('t', 334, 326, 34, 53, 0, 0);
	candara.loadCharacter('u', 213, 384, 42, 46, 0, 0);
	candara.loadCharacter('v', 365, 434, 40, 42, 0, 0);
	candara.loadCharacter('w', 1, 434, 60, 43, 0, 0);
	candara.loadCharacter('x', 466, 383, 44, 46, 0, 0);
	candara.loadCharacter('y', 49, 149, 39, 56, 0, 24);
	candara.loadCharacter('z', 426, 384, 39, 45, 0, 0);
	
	candara.loadCharacter('A', 231, 326, 53, 56, 0, 0);
	candara.loadCharacter('B', 184, 326, 44, 56, 0, 0);
	candara.loadCharacter('C', 456, 149, 44, 56, 0, 0);
	candara.loadCharacter('D', 134, 326, 47, 56, 0, 0);
	candara.loadCharacter('E', 91, 326, 41, 56, 0, 0);
	candara.loadCharacter('F', 49, 326, 39, 56, 0, 0);
	candara.loadCharacter('G', 405, 148, 48, 58, 0, 0);
	candara.loadCharacter('H', 0, 325, 47, 58, 0, 0);
	candara.loadCharacter('I', 353, 82, 22, 60, 0, 0);
	candara.loadCharacter('J', 116, 210, 35, 55, 0, 0);
	candara.loadCharacter('K', 420, 268, 46, 55, 0, 0);
	candara.loadCharacter('L', 379, 269, 38, 54, 0, 0);
	candara.loadCharacter('M', 317, 269, 58, 54, 0, 0);
	candara.loadCharacter('N', 269, 269, 45, 54, 0, 0);
	candara.loadCharacter('O', 350, 148, 54, 58, 0, 0);
	candara.loadCharacter('P', 223, 269, 41, 54, 0, 0);
	candara.loadCharacter('Q', 335, 2, 52, 68, 0, 5);
	candara.loadCharacter('R', 175, 269, 44, 54, 0, 0);
	candara.loadCharacter('S', 306, 148, 43, 59, 0, 0);
	candara.loadCharacter('T', 125, 268, 46, 56, 0, 0);
	candara.loadCharacter('U', 66, 210, 47, 55, 0, 0);
	candara.loadCharacter('V', 73, 268, 50, 56, 0, 0);
	candara.loadCharacter('W', 1, 269, 70, 54, 0, 0);
	candara.loadCharacter('X', 415, 209, 50, 56, 0, 0);
	candara.loadCharacter('Y', 363, 209, 49, 56, 0, 0);
	candara.loadCharacter('Z', 320, 210, 41, 54, 0, 0);
	
	candara.loadCharacter('0', 370, 326, 43, 50, 0, 0);
	candara.loadCharacter('1', 456, 327, 28, 47, 0, 0);
	candara.loadCharacter('2', 415, 326, 39, 49, 0, 0);
	candara.loadCharacter('3', 93, 82, 41, 61, 0, 0);
	candara.loadCharacter('4', 0, 149, 45, 58, 0, 0);
	candara.loadCharacter('5', 219, 83, 39, 59, 0, 0);
	candara.loadCharacter('6', 274, 208, 42, 58, 0, 0);
	candara.loadCharacter('7', 424, 83, 39, 58, 0, 0);
	candara.loadCharacter('8', 235, 149, 42, 57, 0, 0);
	candara.loadCharacter('9', 48, 83, 42, 60, 0, 0);

	candara.loadCharacter('!', 249, 208, 24, 57, 0, 0);
	candara.loadCharacter('@', 233, 2, 70, 74, 0, 0);
	candara.loadCharacter('#', 202, 209, 44, 55, 0, 0);
	candara.loadCharacter('$', 457, 2, 36, 64, 0, 0);
	candara.loadCharacter('%', 286, 325, 45, 58, 0, 0);
	candara.loadCharacter('^', 281, 435, 45, 40, 0, 0);
	candara.loadCharacter('&', 180, 150, 53, 55, 0, 0);
	candara.loadCharacter('*', 194, 434, 41, 41, 0, 0);
	candara.loadCharacter('(', 198, 1, 32, 76, 0, 0);
	candara.loadCharacter(')', 163, 1, 31, 76, 0, 0);
	candara.loadCharacter('-', 125, 480, 28, 19, 0, 0);
	candara.loadCharacter('_', 74, 480, 47, 19, 0, 0);
	candara.loadCharacter('+', 238, 433, 40, 41, 0, 0);
	candara.loadCharacter('=', 418, 432, 42, 35, 0, 0);
	candara.loadCharacter('[', 56, 1, 30, 77, 0, 0);
	candara.loadCharacter(']', 23, 1, 30, 77, 0, 0);
	candara.loadCharacter('{', 126, 1, 35, 76, 0, 0);
	candara.loadCharacter('}', 89, 1, 33, 76, 0, 0);
	candara.loadCharacter('|', 1, 2, 20, 78, 0, 0);
	candara.loadCharacter('\\', 328, 433, 23, 39, 0, 0);
	candara.loadCharacter(';', 0, 209, 25, 56, 0, 0);
	candara.loadCharacter(':', 402, 385, 22, 43, 0, 0);
	candara.loadCharacter('\'', 422, 1, 33, 71, 0, 0);
	candara.loadCharacter('"', 353, 434, 34, 37, 0, 0);
	candara.loadCharacter(',', 391, 434, 23, 33, 0, 0);
	candara.loadCharacter('.', 51, 482, 20, 20, 0, 0);
	candara.loadCharacter('<', 151, 432, 42, 45, 0, 0);
	candara.loadCharacter('>', 108, 432, 41, 45, 0, 0);
	candara.loadCharacter('?', 29, 210, 32, 55, 0, 0);
	candara.loadCharacter('/', 422, 1, 33, 71, 0, 0);
	candara.loadCharacter('`', 462, 433, 27, 25, 0, 0);
	candara.loadCharacter('~', 2, 480, 44, 24, 0, 0);
	fontMap["candara"] = candara;
}