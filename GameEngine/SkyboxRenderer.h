#pragma once

#include "RawModel.h"
#include "SkyboxShader.h"
#include "Loader.h"
#include "Camera.h"
#include <string>
#include <vector>

class SkyboxRenderer
{
public:
	SkyboxRenderer(Loader loader, glm::mat4 projectionMatrix);
	void render(Camera &camera, glm::vec3 fogColor);

private:
	RawModel cube;
	int texture;
	int nightTexture;
	SkyboxShader shader;

	void bindTextures();
};