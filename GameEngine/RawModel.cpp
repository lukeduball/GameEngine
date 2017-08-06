#include "RawModel.h"

RawModel::RawModel(GLuint id, GLuint count) : vaoID(id), vertexCount(count) {}

GLuint RawModel::getVAOID()
{
	return this->vaoID;
}

GLuint RawModel::getVertexCount()
{
	return this->vertexCount;
}