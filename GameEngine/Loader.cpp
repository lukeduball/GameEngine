#include "Loader.h"
#include "RawModel.h"

RawModel Loader::loadToVAO(std::vector<GLfloat> positions, std::vector<GLfloat> textureCoords, std::vector<GLfloat> normals, std::vector<GLuint> indices)
{
	GLuint vaoID = createVAO();
	bindIndicesBuffer(indices);
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, textureCoords);
	storeDataInAttributeList(2, 3, normals);
	unbindVAO();
	return RawModel(vaoID, indices.size());
}

RawModel Loader::loadToVAO(std::vector <GLfloat> positions, int dimensions)
{
	int vaoID = createVAO();
	storeDataInAttributeList(0, dimensions, positions);
	unbindVAO();
	return RawModel(vaoID, positions.size() / dimensions);
}

GLuint Loader::createEmptyVBO(int floatCount)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*floatCount, 0, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return vboID;
}

void Loader::addInstanceAttibute(GLuint vaoID, GLuint vboID, int attribute, int dataSize, int instancedDataLength, int offset)
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBindVertexArray(vaoID);
	glVertexAttribPointer(attribute, dataSize, GL_FLOAT, GL_FALSE, instancedDataLength * 4, (void*)(offset * 4));
	glVertexAttribDivisor(attribute, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Loader::updateVBO(GLuint vboID, std::vector<GLfloat> data)
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data[0])*data.size(), &data[0], GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(data[0])*data.size(), &data[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::cleanUp()
{
	for (GLuint *VAO : vaoList)
	{
		glDeleteVertexArrays(1, VAO);
	}

	for (GLuint *VBO : vboList)
	{
		glDeleteBuffers(1, VBO);
	}

	for (GLuint *textureID : textures)
	{
		glDeleteTextures(1, textureID);
	}
}

GLuint Loader::loadTexture(const GLchar *fileName)
{
	GLuint textureID;

	int width, height;

	unsigned char *image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//Changes the resolution of the mipmapping so that a greater negative value gives higher resolution
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.5);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	if (glewIsSupported("GL_EXT_texture_filter_antisotropic") || GLEW_EXT_texture_filter_anisotropic)
	{
		float ansio = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &ansio);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, ansio);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	this->textures.push_back(&textureID);
	return textureID;
}

GLuint Loader::loadCubeMap(std::string fileName[6])
{
	GLuint textureID;
	int width, height;
	unsigned char *image;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (GLuint i = 0; i < 6; i++)
	{
		std::string path = std::string("resources/images/skybox/").append(fileName[i]);
		image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
	this->textures.push_back(&textureID);
	return textureID;
}


GLuint Loader::createVAO()
{
	GLuint vaoID;
	vaoList.push_back(&vaoID);
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}

void Loader::storeDataInAttributeList(int atrributeNumber, int coordinateSize, std::vector<GLfloat> positions)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vboList.push_back(&vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0])*positions.size(), &positions[0], GL_STATIC_DRAW);
	glVertexAttribPointer(atrributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVAO()
{
	glBindVertexArray(0);
}

void Loader::bindIndicesBuffer(std::vector<GLuint> indices)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vboList.push_back(&vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*indices.size(), &indices[0], GL_STATIC_DRAW);
}