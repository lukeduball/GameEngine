#include "MasterRenderer.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "Light.h"
#include "StaticShader.h"
#include "TerraForge.h"
#include "Camera.h"
#include "ParticleRenderer.h"

const GLfloat MasterRenderer::FOV = 70.0f;
const GLfloat MasterRenderer::NEAR_PLANE = 0.1f;
const GLfloat MasterRenderer::FAR_PLANE = 1000.0f;
const GLfloat MasterRenderer::SKY_RED = 0.5f;
const GLfloat MasterRenderer::SKY_BLUE = 0.65f;
const GLfloat MasterRenderer::SKY_GREEN = 0.6f;

MasterRenderer::MasterRenderer(Loader loader) : projectionMatrix(glm::perspective(FOV, (GLfloat)TerraForge::SCREEN_WIDTH / (GLfloat)TerraForge::SCREEN_HEIGHT, NEAR_PLANE, FAR_PLANE)),
									shader(StaticShader()),
									renderer(EntityRenderer(this->shader, this->projectionMatrix)),
									terrainShader(TerrainShader()),
									terrainRenderer(TerrainRenderer(this->terrainShader, this->projectionMatrix)),
									skyboxRenderer(SkyboxRenderer(loader, this->projectionMatrix))
{
	TerraForge::enableCulling();
}

void MasterRenderer::prepare()
{
	//glClearColor(0.0f, 0.78039216f, 0.76078431f, 1.0f);
	glClearColor(SKY_RED, SKY_GREEN, SKY_BLUE, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::registerModels()
{
	entitiesList = std::vector<std::list<Entity*>>(TexturedModel::nextID);
}

void MasterRenderer::cleanUp()
{
	for (std::list<Entity*> list : entitiesList)
	{
		for (Entity *entity : list)
		{
			delete entity;
		}
	}
}

void MasterRenderer::render(std::vector<Light*> lights, glm::vec4 clipPlane)
{
	glm::vec3 fogColor = glm::vec3(SKY_RED, SKY_GREEN, SKY_BLUE);
	prepare();
	shader.Use();
	shader.loadClipPlane(clipPlane);
	shader.loadSkyColor(fogColor);
	shader.loadLights(lights);
	shader.loadViewCameraMatrix(TerraForge::camera.getViewMatrix());
	renderer.render(entitiesList);
	shader.Stop();

	terrainShader.Use();
	terrainShader.loadClipPlane(clipPlane);
	terrainShader.loadSkyColor(fogColor);
	terrainShader.loadLights(lights);
	terrainShader.loadViewCameraMatrix(TerraForge::camera.getViewMatrix());
	terrainRenderer.render(terrains);
	terrainShader.Stop();

	skyboxRenderer.render(TerraForge::camera, fogColor);
	TerraForge::particleRenderer->render(clipPlane);
}

void MasterRenderer::processEntity(Entity *entity)
{
	int id = entity->getModel().getID();
	if (id < entitiesList.size())
	{
		entitiesList[id].push_back(entity);
	}
	else
	{
		std::cout << "ENTTIY WITH TEXTURED MODEL ID:" + id << " WAS ATTTEMPTED TO BE ADDED WITHOUT BEING REGISTERED TO THE LIST!" << std::endl;
	}
}

void MasterRenderer::processTerrain(Terrain terrain)
{
	terrains.push_back(terrain);
}

std::vector<std::list<Entity*>> MasterRenderer::getEntityLists()
{
	return this->entitiesList;
}

glm::mat4 MasterRenderer::getProjectionMatrix()
{
	return this->projectionMatrix;
}

void TerraForge::enableCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void TerraForge::disableCulling()
{
	glDisable(GL_CULL_FACE);
}