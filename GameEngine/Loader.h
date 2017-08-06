#pragma once

#include <vector>
#include <list>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <SOIL2/SOIL2.h>

class RawModel;

class Loader
{
public: 
	RawModel loadToVAO(std::vector <GLfloat> positions, std::vector<GLfloat> textureCoords, std::vector<GLfloat> normals, std::vector<GLuint> indices);
	RawModel loadToVAO(std::vector <GLfloat> positions, int dimensions);

	GLuint createEmptyVBO(int floatCount);
	void addInstanceAttibute(GLuint vaoID, GLuint vboID, int attribute, int dataSize, int instancedDataLength, int offset);
	void updateVBO(GLuint vboID, std::vector<GLfloat> data);

	void cleanUp();

	GLuint loadTexture(const GLchar *fileName);
	GLuint loadCubeMap(std::string fileName[6]);
	
private:
	std::list<GLuint*> vaoList;
	std::list<GLuint*> vboList;
	std::list<GLuint*> textures;
 
	GLuint createVAO();
	
	void storeDataInAttributeList(int atrributeNumber, int coordinateSize, std::vector<GLfloat> positions);

	void unbindVAO();

	void bindIndicesBuffer(std::vector<GLuint> indices);

};