#include "Shader.h"

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
{
	std::string str = vertexPath;
	str = str.substr(str.find_last_of("/") + 1);
	this->shaderIdentifier = str.substr(0, str.size() - 3);

	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		//Open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		//Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//close file handlers
		vShaderFile.close();
		fShaderFile.close();
		//Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	// 2. Compile the Shaders
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	//Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	//Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX " << vertexPath << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	//Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR:SHADER::FRAGMENT" << fragmentPath << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//Shader Program
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	//Print Linking Errors if any
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	//Delete the shaders as they are linked into our program now and are no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::getAllUniformLocations() {}

//Uses the current shader
void Shader::Use()
{
	glUseProgram(this->Program);
}

//Stops the current shader
void Shader::Stop()
{
	glUseProgram(0);
}

GLuint Shader::getUniformLocation(const GLchar *uniformName)
{
	return glGetUniformLocation(this->Program, uniformName);
}

void Shader::loadFloat(GLuint location, GLfloat value)
{
	glUniform1f(location, value);
}

void Shader::loadVector(GLuint location, glm::vec3 vector)
{
	glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::loadVector2(GLuint location, glm::vec2 vector)
{
	glUniform2f(location, vector.x, vector.y);
}

void Shader::loadVector4(GLuint location, glm::vec4 vector)
{
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void Shader::loadBoolean(GLuint location, bool value)
{
	float val = 0;
	if (value)
	{
		val = 1;
	}
	loadFloat(location, val);
}

void Shader::loadMatrix(GLuint location, glm::mat4 matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::loadInt(GLuint location, GLuint value)
{
	glUniform1i(location, value);
}