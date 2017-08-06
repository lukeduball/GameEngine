#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

class ModelTexture 
{
public:
	ModelTexture(GLuint id);

	GLuint getID();
	GLfloat getShineDamper();
	GLfloat getReflectivity();
	void setShineDamper(GLfloat damper);
	void setReflectivity(GLfloat reflect);

	void setTransparency(bool flag);
	bool hasTrasparency();
	void setFakeLighting(bool flag);
	bool useFakeLighting();

	void setNumberOfRows(int i);
	int getNumberOfRows();

private:
	GLuint textureID;
	GLfloat shineDamper = 40.0f;
	GLfloat reflectivity = 0.0f;
	bool hasTransparency = false;
	bool fakeLighting = false;
	int numberOfRows = 1;
};