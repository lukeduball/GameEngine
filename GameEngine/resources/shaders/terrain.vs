#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

out vec2 TexCoords;
out vec3 surfaceNormal;
out vec3 toLightVector[4];
out vec3 toCameraVector;
out float visability;

uniform mat4 transformationMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition[4];

//FOGGY VALUES
//const float density = 0.007;
//const float gradient = 1.5;
const float density = 0.0035;
const float gradient = 5.0;

uniform vec4 plane;

void main()
{
	vec4 worldPosition = transformationMatrix * vec4(position, 1.0);

	gl_ClipDistance[0] = dot(worldPosition, plane);

	vec4 positionRelativeToCam = view * worldPosition;
	gl_Position = projection * positionRelativeToCam;
	TexCoords = texCoords;

	surfaceNormal = (transformationMatrix * vec4(normal, 0.0)).xyz;
	for(int i = 0; i < 4; i++)
	{
			toLightVector[i] = lightPosition[i] - worldPosition.xyz;
	}
	toCameraVector = (inverse(view) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;

	float distance = length(positionRelativeToCam.xyz);
	visability = exp(-pow((distance*density), gradient));
	visability = clamp(visability, 0.0, 1.0);
}