#version 330 core

in vec2 outTextureCoords;

out vec4 outColor;

uniform vec3 color;
uniform sampler2D fontAtlas;

uniform float width;
uniform float edge;

uniform float borderWidth;
uniform float borderEdge;

uniform vec2 offset;

uniform vec3 outlineColor;

void main()
{
	float distance = 1.0 - texture(fontAtlas, outTextureCoords).a;
	float alpha = 1.0 - smoothstep(width, width+edge, distance);

	float distance2 = 1.0 - texture(fontAtlas, outTextureCoords + offset).a;
	float outlineAlpha = 1.0 - smoothstep(borderWidth, borderWidth+borderEdge, distance2);

	float overallAlpha = alpha + (1.0 - alpha) * outlineAlpha;
	vec3 overallColor = mix(outlineColor, color, alpha / overallAlpha);

	outColor = vec4(overallColor, overallAlpha);
}