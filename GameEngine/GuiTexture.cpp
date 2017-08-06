#include "GuiTexture.h"

GuiTexture::GuiTexture(int texture, glm::vec2 position, glm::vec2 scale) : textureID(texture), position(position), scale(scale) {}

int	GuiTexture::getTexture()
{
	return this->textureID;
}

glm::vec2 GuiTexture::getPosition()
{
	return this->position;
}

glm::vec2 GuiTexture::getScale()
{
	return this->scale;
}