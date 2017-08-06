#pragma once

#include <vector>
#include <iostream>
#include <list>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

class Player;
class Shader;
class Camera;
class GameObject;
class Terrain;
class ParticleRenderer;

class TerraForge
{
public:
	static const int MAX_LIGHTS = 4;
	static int SCREEN_WIDTH, SCREEN_HEIGHT;

	static Camera camera;
	static bool keys[1024];
	static float mouseX, mouseY;

	static bool freeCamera;
	static bool wireFrame;

	//Vectors are better for data added to the end and can be randomly accessed
	//Lists are good for data that changes and is continally added and removed -- has to be iterated through
	//GameObject List -> kill game objects on next iteration during update -- maybe boolean value to decide to remove or call functions

	static Player *thePlayer;
	static Terrain *currentTerrain;

	static ParticleRenderer *particleRenderer;

	static GLfloat deltaTime;

	static std::string skyboxPaths[6];
	static std::string nightBoxPaths[6];

	static const float GRAVITY;

	static void enableCulling();
	static void disableCulling();

};