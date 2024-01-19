#include "ShaderProgram.h"

#include <iostream>
#include <sstream>
#include <fstream>

void ShaderProgram::AddShaders(GLenum type, std::string name)
{
	Shader compiledShader = CompileShader(type, name);
	shaders.push_back(compiledShader);
}

void ShaderProgram::Link()
{
	id = glCreateProgram();

	for (auto& shader : shaders)
	{
		glAttachShader(id, shader.id);
	}
	glLinkProgram(id);

	GLint success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	for (auto& shader : shaders)
	{
		glDetachShader(id, shader.id);
		glDeleteShader(shader.id);
	}
}

GLuint ShaderProgram::ID() const
{
	return id;
}

std::vector<Shader> ShaderProgram::Shaders() const
{
	return shaders;
}

GLint ShaderProgram::UniformLocation(std::string name) const
{
	return glGetUniformLocation(id, name.c_str());
}

Shader ShaderProgram::CompileShader(GLenum type, std::string filename)
{
	Shader result;
	result.type = type;
	result.filename = filename;

	// 1. Load file content
	std::string shaderSource;
	try
	{
		std::ifstream shaderFile(filename);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderSource = shaderStream.str();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	// 2.  Create shader and compile it
	result.id = glCreateShader(type);
	const GLchar* source = shaderSource.c_str();
	glShaderSource(result.id, 1, &source, nullptr);
	glCompileShader(result.id);

	GLint compiled = GL_FALSE;
	glGetShaderiv(result.id, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(result.id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(result.id, infoLogLength, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		delete[] infoLog;
		result.id = 0;
	}

	return result;
}