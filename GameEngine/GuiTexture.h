#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GuiTexture
{
public:
	GuiTexture(int texture, glm::vec2 position, glm::vec2 scale);
	int getTexture();
	glm::vec2 getPosition();
	glm::vec2 getScale();

private:
	int textureID;
	glm::vec2 position;
	glm::vec2 scale;
};