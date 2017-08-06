#include "GuiRenderer.h"
#include "Maths.h"

#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>

GuiRenderer::GuiRenderer(Loader loader) : quad(loader.loadToVAO(std::vector<GLfloat>{ -1, 1, -1, -1, 1, 1, 1, -1 }, 2)), shader(GuiShader()) {}

void GuiRenderer::render(std::list<GuiTexture> guis)
{
	shader.Use();
	glBindVertexArray(quad.getVAOID());
	glEnableVertexAttribArray(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	for (GuiTexture gui : guis)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gui.getTexture());
		glm::mat4 transformMatrix = Maths::createTransformationMatrix(gui.getPosition(), gui.getScale());
		shader.loadTransformationMatrix(transformMatrix);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, quad.getVertexCount());
	}
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.Stop();
}