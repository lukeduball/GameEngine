#pragma once

#include <vector>
#include <list>

#include "EntityRenderer.h"
#include "StaticShader.h"

#include "TerrainShader.h"
#include "TerrainRenderer.h"

#include "SkyboxRenderer.h"
#include "Loader.h"

class Light;
class Entity;
class TexturedModel;

class MasterRenderer
{
public:
	MasterRenderer(Loader loader);

	void cleanUp();

	void render(std::vector<Light*> lights, glm::vec4 clipPlane);
	void processEntity(Entity *entity);
	void processTerrain(Terrain terrain);
	void prepare();
	void registerModels();
	std::vector<std::list<Entity*>> getEntityLists();
	glm::mat4 getProjectionMatrix();

	static const GLfloat FOV;
	static const GLfloat NEAR_PLANE;
	static const GLfloat FAR_PLANE;
	static const GLfloat SKY_RED;
	static const GLfloat SKY_BLUE;
	static const GLfloat SKY_GREEN;

private:
	int timeOfDay;
	const int DAY_TIME_CYCLE = 0;
	glm::mat4 projectionMatrix;

	std::vector<std::list<Entity*>> entitiesList;

	StaticShader shader;
	EntityRenderer renderer;

	TerrainShader terrainShader;
	TerrainRenderer terrainRenderer;
	std::list<Terrain> terrains;

	SkyboxRenderer skyboxRenderer;
};