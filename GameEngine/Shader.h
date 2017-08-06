#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	GLuint Program;
	std::string shaderIdentifier;

	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

	//Uses the current shader
	void Use();

	//Stops the current shader
	void Stop();

protected:
	virtual void getAllUniformLocations() = 0;

	GLuint getUniformLocation(const GLchar *uniformName);

	void loadFloat(GLuint location, GLfloat value);

	void loadVector(GLuint location, glm::vec3 vector);

	void loadVector2(GLuint location, glm::vec2 vector);

	void loadVector4(GLuint location, glm::vec4 vector);
	
	void loadBoolean(GLuint location, bool value);

	void loadMatrix(GLuint location, glm::mat4 matrix);

	void loadInt(GLuint location, GLuint value);
};
