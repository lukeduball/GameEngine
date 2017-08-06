#pragma once

#include "RawModel.h"
#include "ModelTexture.h"

class TexturedModel
{
public:
	TexturedModel(RawModel model, ModelTexture texture);

	RawModel getRawModel();
	ModelTexture* getTexture();
	int getID();
	static int nextID;

private:
	RawModel rawModel;
	ModelTexture texture;
	int ID;
};