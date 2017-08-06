#pragma once

#include "Loader.h"
#include "RawModel.h"
#include "GuiTexture.h"
#include "GuiShader.h"
#include <list>

class GuiRenderer
{
public:
	GuiRenderer(Loader loader);
	void render(std::list<GuiTexture> guis);

private:
	RawModel quad;
	GuiShader shader;
};