#version 330 core

layout (location = 0) in vec2 position;

out vec2 outTextureCoords;

uniform mat4 translation;
uniform vec4 textureCoords;

void main()
{
	gl_Position = translation * vec4(position, 0.0, 1.0);

	float xTexture = 0.0;
	float yTexture = 0.0;
	if(position.x == -1)
	{
		xTexture = textureCoords.x;
	}
	else
	{
		xTexture = textureCoords.z;
	}

	if(position.y == 1)
	{
		yTexture = textureCoords.y;
	}
	else
	{
		yTexture = textureCoords.w;
	}
	outTextureCoords = vec2(xTexture, yTexture);
}