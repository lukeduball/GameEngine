#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

class ShadowDepthBuffer
{
public:
	ShadowDepthBuffer();
	void bindShadowBuffer();
	void unbindFrameBuffer();
	GLuint getShadowDepthTexture();
	void cleanUp();
private:
	static const int SHADOW_WIDTH;
	static const int SHADOW_HEIGHT;
	GLuint shadowBuffer;
	GLuint shadowDepthTexture;
};