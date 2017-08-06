#include "TexturedModel.h"
#include "RawModel.h"
#include "ModelTexture.h"
#include <iostream>

TexturedModel::TexturedModel(RawModel model, ModelTexture texture) : rawModel(model), texture(texture), ID(nextID) 
{
	TexturedModel::nextID++;
	std::cout << nextID << "\n";
}

RawModel TexturedModel::getRawModel()
{
	return this->rawModel;
}

ModelTexture *TexturedModel::getTexture()
{
	return &this->texture;
}

int TexturedModel::getID()
{
	return ID;
}

int TexturedModel::nextID = 0;