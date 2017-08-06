#include "TerraForge.h"
#include "Player.h"
#include "Camera.h"
#include "StaticShader.h"
#include "Loader.h"
#include "RawModel.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Maths.h"
#include "OBJLoader.h"
#include "Light.h"
#include "MasterRenderer.h"

#include "GuiRenderer.h"
#include "GuiTexture.h"
#include "FontRenderer.h"

#include "EntityLamp.h"

#include "ParticleRenderer.h"
#include "ParticleSystem.h"
#include "Particle.h"

#include "MousePicker.h"

#include "WaterRenderer.h"
#include "WaterTile.h"
#include "WaterFrameBuffers.h"

#include "ShadowDepthBuffer.h"
#include "ShadowRenderer.h"

#include "ReshapableTerrain.h"

#include <random>

const float TerraForge::GRAVITY = -50.0f;
Camera TerraForge::camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool TerraForge::keys[1024];
bool TerraForge::freeCamera = false;
bool TerraForge::wireFrame = false;
Player *TerraForge::thePlayer;
Terrain *TerraForge::currentTerrain;
ParticleRenderer *TerraForge::particleRenderer;

std::string TerraForge::skyboxPaths[6] = { std::string("right.png"), std::string("left.png"), std::string("top.png") , std::string("bottom.png"), std::string("back.png"), std::string("front.png") };
std::string TerraForge::nightBoxPaths[6] = { std::string("nightRight.png"), std::string("nightLeft.png"), std::string("nightTop.png") , std::string("nightBottom.png"), std::string("nightBack.png"), std::string("nightFront.png") };


const GLint WIDTH = 1200, HEIGHT = 1000;
int TerraForge::SCREEN_WIDTH, TerraForge::SCREEN_HEIGHT;

float TerraForge::mouseX = WIDTH / 2.0f;
float TerraForge::mouseY = HEIGHT / 2.0f;

GLfloat TerraForge::deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

bool firstMouse = true;

double lastTick = 0.0;

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset);
void renderDebugStrings(FontRenderer &fontRenderer);

int main()
{
	ReshapableTerrain funcTester = ReshapableTerrain();
	funcTester.vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
	funcTester.vertices.push_back(glm::vec3(0.0, 10.0, 0.0));
	funcTester.vertices.push_back(glm::vec3(10.0, 0.0, 0.0));
	funcTester.triangleReshape(glm::vec3(3.0, 3.0, 0.0), glm::vec3(3.0, 5.0, 0.0), glm::vec3(5.0, 3.0, 0.0));
	
	
	//std::cout << funcTester.doLinesIntersect(glm::vec3(1, 0, 0), glm::vec3(3, 3, 1), glm::vec3(0, 5, 5), glm::vec3(5, 6, 2)) << "\n";
	//Intersecting glm::vec3(1, 0, 0), glm::vec3(3, 3, 1), glm::vec3(0, 5, 5), glm::vec3(5, 6, 2)
	//5, 6, 2
	return 0;

	glfwInit();
	
	//Sets up the window context with major and if that fails goes to minor
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //This gets the methods for the new modern openGL instead of the compatability mode
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); //Sets if the screen is resizable

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Game Engine", nullptr, nullptr); //Creates the window pointer

	glfwGetFramebufferSize(window, &TerraForge::SCREEN_WIDTH, &TerraForge::SCREEN_HEIGHT);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;

		return EXIT_FAILURE;
	}

	glViewport(0, 0, TerraForge::SCREEN_WIDTH, TerraForge::SCREEN_HEIGHT);
	
	Loader loader = Loader();
	FontRenderer fontRenderer = FontRenderer(loader);
	
	TexturedModel treeModel = TexturedModel(OBJLoader::loadModel("pine", loader), ModelTexture(loader.loadTexture("resources/images/pine.png")));
	treeModel.getTexture()->setShineDamper(40.0f);
	treeModel.getTexture()->setReflectivity(0.0f);
	treeModel.getTexture()->setFakeLighting(true);
	treeModel.getTexture()->setTransparency(true);
	TexturedModel tallGrassModel = TexturedModel(OBJLoader::loadModel("grassModel", loader), ModelTexture(loader.loadTexture("resources/images/grassTexture.png")));
	tallGrassModel.getTexture()->setShineDamper(40.0f);
	tallGrassModel.getTexture()->setReflectivity(0.0f);
	tallGrassModel.getTexture()->setTransparency(true);
	tallGrassModel.getTexture()->setFakeLighting(true);
	TexturedModel fernModel = TexturedModel(OBJLoader::loadModel("fern", loader), ModelTexture(loader.loadTexture("resources/images/fern.png")));
	fernModel.getTexture()->setShineDamper(40.0f);
	fernModel.getTexture()->setReflectivity(0.0f);
	fernModel.getTexture()->setTransparency(true);
	fernModel.getTexture()->setFakeLighting(true);
	fernModel.getTexture()->setNumberOfRows(2);

	TexturedModel lampModel = TexturedModel(OBJLoader::loadModel("lamp", loader), ModelTexture(loader.loadTexture("resources/images/lamp.png")));
	lampModel.getTexture()->setFakeLighting(true);
	lampModel.getTexture()->setTransparency(true);

	RawModel model = OBJLoader::loadModel("stall", loader);

	TexturedModel texturedModel = TexturedModel(model, ModelTexture(loader.loadTexture("resources/images/stallTexture.png")));
	texturedModel.getTexture()->setShineDamper(10.0f);
	texturedModel.getTexture()->setReflectivity(1.0f);

	TexturedModel bunny = TexturedModel(OBJLoader::loadModel("person", loader), ModelTexture(loader.loadTexture("resources/images/playerTexture.png")));

	TexturedModel cube = TexturedModel(OBJLoader::loadModel("cube", loader), ModelTexture(loader.loadTexture("resources/images/mud.png")));

	glEnable(GL_DEPTH_TEST);

	MasterRenderer renderer = MasterRenderer(loader);
	//All models must be defined and loaded before this call!
	renderer.registerModels();
	ShadowRenderer shadowRenderer = ShadowRenderer();

	//-----------------------------------------------PARTICLE TEXTURES/RENDERER--------------------------------------------------
	ParticleTexture starParticle = ParticleTexture(loader.loadTexture("resources/images/particles/particleAtlas.png"), 4);
	
	ParticleRenderer theParticleRenderer = ParticleRenderer(loader, renderer.getProjectionMatrix());
	TerraForge::particleRenderer = &theParticleRenderer;
	//---------------------------------------------END PARTICLE TEXTUERS/RENDERER------------------------------------------------

	TerrainTexturePack texturePack = TerrainTexturePack(TerrainTexture(loader.loadTexture("resources/images/grassy2.png")), TerrainTexture(loader.loadTexture("resources/images/dirt.png")), TerrainTexture(loader.loadTexture("resources/images/mud.png")), TerrainTexture(loader.loadTexture("resources/images/path.png")));
	TerrainTexture blendMap = TerrainTexture(loader.loadTexture("resources/images/blendMap.png"));
	Terrain terrain = Terrain(0, 0, loader, texturePack, blendMap, "resources/images/heightmap.png");
	TerraForge::currentTerrain = &terrain;
	renderer.processTerrain(terrain);

	// -------------------------------------------------LIGHT SOURCES------------------------------------------------------------
	std::vector<Light*> lights;
	Light sun = Light(glm::vec3(10000.0f, 10000.0f, 10000.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	lights.push_back(&sun);
	EntityLamp *lamp1 = new EntityLamp(lampModel, glm::vec3(350.0f, terrain.getHeightOfTerrain(350.0f, 400.0f), 400.0f), 0.0f, 0.0f, 0.0f, 1.0f, glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(1, 0.01f, 0.002f));
	lights.push_back(lamp1->getLight());
	renderer.processEntity(lamp1);
	EntityLamp *lamp2 = new EntityLamp(lampModel, glm::vec3(450.0f, terrain.getHeightOfTerrain(450.0f, 450.0f), 450.0f), 0.0f, 0.0f, 0.0f, 1.0f, glm::vec3(0.0f, 2.0f, 2.0f), glm::vec3(1, 0.01f, 0.002f));
	lights.push_back(lamp2->getLight());
	renderer.processEntity(lamp2);
	EntityLamp *lamp3 = new EntityLamp(lampModel, glm::vec3(550.0f, terrain.getHeightOfTerrain(550.0f, 500.0f), 500.0f), 0.0f, 0.0f, 0.0f, 1.0f, glm::vec3(2.0f, 2.0f, 0.0f), glm::vec3(1, 0.01f, 0.002f));
	lights.push_back(lamp3->getLight());
	renderer.processEntity(lamp3);

	//------------------------------------------------LIGHT SOURCES END----------------------------------------------------------

	Player *player = new Player(bunny, glm::vec3(347.0f, 100.0f, 46.0f), 0.0f, 0.0f, 0.0f, 1.0f);
	renderer.processEntity(player);

	srand(0);
	int counter = 0;
	for (int i = 0; i < 300; i++)
	{
		float x = (rand() % 500) + 300;
		float z = (rand() % 500) + 300;
		float y = terrain.getHeightOfTerrain(x, z);
		Entity *entity;
		if (counter < 3)
		{
			entity = new Entity(fernModel, (rand() % 4), glm::vec3(x, y, z), 0.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			entity = new Entity(treeModel, glm::vec3(x, y, z), 0.0f, 0.0f, 0.0f, 3.0f);
			counter = -1;
		}
		renderer.processEntity(entity);
		counter++;
	}

	Entity *treeEnt = new Entity(treeModel, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 3.0f);
	renderer.processEntity(treeEnt);
	//----------------------------------------WATER STUFF---------------------------------------------------------
	WaterFrameBuffers fbos = WaterFrameBuffers();
	WaterRenderer waterRenderer = WaterRenderer(loader, renderer.getProjectionMatrix(), fbos);
	std::list<WaterTile> water;
	WaterTile waterTile = WaterTile(412.0f, -12.0f, 97.0f);
	water.push_back(waterTile);
	//--------------------------------------END WATER STUFF-------------------------------------------------------

	// -----------------------------------------GUI STUFF---------------------------------------------------------
	std::list<GuiTexture> guis;
	//GuiTexture gui = GuiTexture(loader.loadTexture("resources/images/XenofrostBlack.png"), glm::vec2(-0.868654f, 0.85f), glm::vec2(0.131345f, 0.15f));
	//guis.push_back(gui);
	GuiTexture shadowMap = GuiTexture(shadowRenderer.getDepthBuffer().getShadowDepthTexture(), glm::vec2(-0.5f, 0.5f), glm::vec2(0.25f, 0.25f));
	guis.push_back(shadowMap);
	GuiRenderer guiRenderer = GuiRenderer(loader);
	// ---------------------------------------END GUI STUFF-------------------------------------------------------


	MousePicker picker = MousePicker(TerraForge::camera, renderer.getProjectionMatrix());

	ParticleSystem psystem = ParticleSystem(starParticle, 50.0f, 25.0f, 0.3f, 4.0f, 1.0f);
	psystem.randomRotation();
	psystem.setDirection(glm::vec3(0.0f, 1.0f, 0.0f), 0.3f);
	psystem.setLifeOffset(0.1f);
	psystem.setSpeedOffset(0.4f);
	psystem.setScaleOffset(0.8f);

	while (!glfwWindowShouldClose(window))
	{
		if (TerraForge::wireFrame)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		//Gets the current time in seconds
		GLfloat currentFrame = glfwGetTime();
		TerraForge::deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		picker.update();
		//std::cout << picker.getCurrentRay().x << ":" << picker.getCurrentRay().y << ":" << picker.getCurrentRay().z << std::endl;
		
		theParticleRenderer.update();
		psystem.spawnParticles(glm::vec3(250.0f, 20.0f, 250.0f));

		//Check to see the amount of time passed to call a game tick -- 0.05 is equal to 20 ticks a second
		//if (currentFrame - lastTick >= 0.05)
		//{
			for (std::list<Entity*> list : renderer.getEntityLists())
			{
				for (Entity *entity : list)
				{
					entity->Update();
				}
			}
			lastTick = currentFrame;
		//}
		//shadowRenderer.render(renderer.getEntityLists(), sun);
			shadowRenderer.render(renderer.getEntityLists(), sun);

		glEnable(GL_CLIP_DISTANCE0);
		fbos.bindReflectionFrameBuffer();
		float distance = 2 * (TerraForge::camera.getPosition().y - waterTile.getHeight());
		TerraForge::camera.setPosition(glm::vec3(TerraForge::camera.getPosition().x, TerraForge::camera.getPosition().y - distance, TerraForge::camera.getPosition().z));
		TerraForge::camera.invertPitch();
		renderer.render(lights, glm::vec4(0, 1, 0, -waterTile.getHeight() + 1.0f));
		TerraForge::camera.setPosition(glm::vec3(TerraForge::camera.getPosition().x, TerraForge::camera.getPosition().y + distance, TerraForge::camera.getPosition().z));
		TerraForge::camera.invertPitch();
		fbos.unbindCurrentFrameBuffer();

		fbos.bindRefractionFrameBuffer();
		renderer.render(lights, glm::vec4(0, -1, 0, waterTile.getHeight()));
		fbos.unbindCurrentFrameBuffer();

		glDisable(GL_CLIP_DISTANCE0);
		renderer.render(lights, glm::vec4(0, -1, 0, 100000000000));
		waterRenderer.render(water, sun);

		guiRenderer.render(guis);
		renderDebugStrings(fontRenderer);

		glfwSwapBuffers(window);
	}

	fbos.cleanUp();
	theParticleRenderer.cleanUp();
	renderer.cleanUp();
	loader.cleanUp();
	glfwTerminate();
	return EXIT_SUCCESS;
}

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		if (TerraForge::freeCamera == true)
		{
			TerraForge::freeCamera = false;
		}
		else
		{
			TerraForge::freeCamera = true;
		}
	}

	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		if (TerraForge::wireFrame)
			TerraForge::wireFrame = false;
		else
			TerraForge::wireFrame = true;
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			TerraForge::keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			TerraForge::keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
	if (firstMouse)
	{
		TerraForge::mouseX = xPos;
		TerraForge::mouseY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - TerraForge::mouseX;
	GLfloat yOffset = TerraForge::mouseY - yPos;

	TerraForge::mouseX = xPos;
	TerraForge::mouseY = yPos;
	if (TerraForge::keys[GLFW_KEY_LEFT_SHIFT])
	{
		TerraForge::camera.ProcessMouseMovement(xOffset, yOffset);
	}
}

void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
	TerraForge::camera.ProcessMouseScroll(yOffset);
}

void renderDebugStrings(FontRenderer &fontRenderer)
{
	fontRenderer.setCurrentFont("candara");
	fontRenderer.setFontSize(0);
	std::string playerPos = std::string("X:").append(std::to_string(TerraForge::thePlayer->getPosition().x)).append(" Y:").append(std::to_string(TerraForge::thePlayer->getPosition().y)).append(" Z:").append(std::to_string(TerraForge::thePlayer->getPosition().z));
	std::string cameraPos = std::string("X:").append(std::to_string(TerraForge::camera.getPosition().x)).append(" Y:").append(std::to_string(TerraForge::camera.getPosition().y)).append(" Z:").append(std::to_string(TerraForge::camera.getPosition().z));
	fontRenderer.renderString(std::string("Player Position: ").append(playerPos), -0.95f, 0.9f, glm::vec3(0.0f, 0.0f, 0.0f));
	fontRenderer.renderString(std::string("Camera Position: ").append(cameraPos), -0.95f, 0.85f, glm::vec3(0.0f, 0.0f, 0.0f));
}