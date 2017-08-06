#pragma once

#include <list>
#include "RawModel.h"
#include "WaterShader.h"
#include "Loader.h"
#include "WaterTile.h"
#include "WaterFrameBuffers.h"
#include "Light.h"

class WaterRenderer
{
public:
	WaterRenderer(Loader loader, glm::mat4 projectionMatrix, WaterFrameBuffers &fbos);
	void render(std::list<WaterTile> water, Light sun);
private:
	static const float WAVE_SPEED;
	float moveFactor = 0;
	RawModel quad;
	WaterShader shader;
	WaterFrameBuffers fbos;
	GLuint dudvTexture;
	GLuint normalTexture;
	void prepareRender(Light sun);
	void finishRender();
};

