#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

class WaterFrameBuffers 
{
public:
	WaterFrameBuffers();
	void cleanUp();
	void bindReflectionFrameBuffer();
	void bindRefractionFrameBuffer();
	void unbindCurrentFrameBuffer();
	int getReflectionTexture();
	int getRefractionTexture();
	int getRefractionDepthTexture();

private:
	static const int REFLECTION_WIDTH;
	static const int REFLECTION_HEIGHT;

	static const int REFRACTION_WIDTH;
	static const int REFRACTION_HEIGHT;

	GLuint reflectionFrameBuffer;
	GLuint reflectionTexture;
	GLuint reflectionDepthBuffer;

	GLuint refractionFrameBuffer;
	GLuint refractionTexture;
	GLuint refractionDepthTexture;

	void initializeReflectionFrameBuffer();
	void initializeRefractionFrameBuffer();
	void bindFrameBuffer(GLuint frameBuffer, int width, int height);
	int createFrameBuffer();
	int createTextureAttachment(int width, int height);
	int createDepthTextureAttachment(int width, int height);
	int createDepthBufferAttachment(int width, int height);
};