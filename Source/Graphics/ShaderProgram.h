#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>

struct Shader {
	GLenum type;
	std::string filename;
	int id;
};

class ShaderProgram {
public:
	template <typename... Shaders>
	void AddShaders(GLenum type, std::string name, Shaders... shaders) {
		AddShaders(type, name);
		AddShaders(shaders...);
	}

	void AddShaders(GLenum type, std::string name);
	void Link();

	GLuint ID() const;
	std::vector<Shader> Shaders() const;
	GLint UniformLocation(std::string name) const;
private:
	Shader CompileShader(GLenum type, std::string filename);
private:
	GLuint id;
	std::vector<Shader> shaders;
};