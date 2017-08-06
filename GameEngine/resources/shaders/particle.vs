#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in mat4 viewMatrix;
layout (location = 5) in vec4 texOffsets;
layout (location = 6) in float blendFactor;

out vec2 textureCoords1;
out vec2 textureCoords2;
out float blend;

uniform mat4 projectionMatrix;
uniform float numberOfRows;

void main()
{
	vec2 textureCoords = position + vec2(0.5, 0.5);
	textureCoords.y = 1.0 - textureCoords.y;
	textureCoords /= numberOfRows;
	textureCoords1 = textureCoords + texOffsets.xy;
	textureCoords2 = textureCoords + texOffsets.zw;
	blend = blendFactor;

	gl_Position = projectionMatrix * viewMatrix * vec4(position, 0.0, 1.0);
}