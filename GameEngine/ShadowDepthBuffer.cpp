#include "ShadowDepthBuffer.h"
#include "TerraForge.h"

const int ShadowDepthBuffer::SHADOW_WIDTH = 2048;
const int ShadowDepthBuffer::SHADOW_HEIGHT = 2048;

ShadowDepthBuffer::ShadowDepthBuffer()
{
	glGenFramebuffers(1, &shadowBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowBuffer);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glGenTextures(1, &shadowDepthTexture);
	glBindTexture(GL_TEXTURE_2D, shadowDepthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowDepthTexture, 0);
	unbindFrameBuffer();
	
}

void ShadowDepthBuffer::bindShadowBuffer()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowBuffer);
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
}

void ShadowDepthBuffer::unbindFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, TerraForge::SCREEN_WIDTH, TerraForge::SCREEN_HEIGHT);
}

GLuint ShadowDepthBuffer::getShadowDepthTexture()
{
	return shadowDepthTexture;
}

void ShadowDepthBuffer::cleanUp()
{
	glDeleteFramebuffers(1, &shadowBuffer);
	glDeleteTextures(1, &shadowDepthTexture);
}
