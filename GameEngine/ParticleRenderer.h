#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <list>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Loader.h"
#include "ParticleShader.h"
#include "RawModel.h"

class Particle;

class ParticleRenderer
{
public:
	ParticleRenderer(Loader &loader, glm::mat4 projection);
	void render(glm::vec4 clipPlane);
	void cleanUp();
	void prepare();
	void update();
	void addParticle(Particle *particle);
private:
	const int MAX_INSTANCES = 10000;
	const int INSTANCE_DATA_LENGTH = 21;
	GLuint vbo;
	Loader loader;
	RawModel quad;
	ParticleShader shader;
	std::map<int, std::list<Particle*>> particlesMap;
	int pointer = 0;

	void updateModelViewMatrix(glm::vec3 position, float rotation, float scale, glm::mat4 viewMatrix, std::vector<GLfloat> &vboData);
	void storeMatrixData(glm::mat4 matrix, std::vector<GLfloat> &vboData);
	void finishRendering();
};