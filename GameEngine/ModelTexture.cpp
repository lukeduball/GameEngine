#include "ModelTexture.h"

ModelTexture::ModelTexture(GLuint id) : textureID(id) {}

GLuint ModelTexture::getID()
{
	return this->textureID;
}

GLfloat ModelTexture::getShineDamper()
{
	return this->shineDamper;
}

GLfloat ModelTexture::getReflectivity()
{
	return this->reflectivity;
}

void ModelTexture::setShineDamper(GLfloat damper)
{
	this->shineDamper = damper;
}

void ModelTexture::setReflectivity(GLfloat reflect)
{
	this->reflectivity = reflect;
}

void ModelTexture::setTransparency(bool flag)
{
	this->hasTransparency = flag;
}

bool ModelTexture::hasTrasparency()
{
	return this->hasTransparency;
}

void ModelTexture::setFakeLighting(bool flag)
{
	this->fakeLighting = flag;
}

bool ModelTexture::useFakeLighting()
{
	return this->fakeLighting;
}

void ModelTexture::setNumberOfRows(int i)
{
	this->numberOfRows = i;
}

int ModelTexture::getNumberOfRows()
{
	return this->numberOfRows;
}