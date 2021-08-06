#include <fstream>
#include <iostream>

#include "shader.hpp"

std::string getText(std::string filename) {
	std::string res, str = "";
	std::ifstream in;
	in.open(filename.c_str());
	if (in.is_open()) {
		getline(in, str);
		while (in) {
			res += str + "\n";
			getline(in, str);
		}
		return res;
	} else {
		std::cerr << "Unable to Open File " << filename << "\n";
		throw 2;
	}
}

unsigned int compile_shader(std::string filename) {
	std::string source = getText(filename);

	// Get type of shader
	unsigned int shader;
	if (filename.substr(filename.find_last_of (".") + 1) == "vs") {
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (filename.substr(filename.find_last_of (".") + 1) == "fs") {
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else {
		std::cout << "Error compiling shader: Extension not recognized\n";
		return -1;
	}

	// Compile shader
	const char *source_as_c_str = source.c_str();
	glShaderSource(shader, 1, &source_as_c_str, NULL);
	glCompileShader(shader);

	// Check for errors
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Error compiling shader: " << infoLog << ":c\n";
	}

	return shader;
}

unsigned int create_shader(std::string vertex_shader, std::string fragment_shader) {
	unsigned int vs = compile_shader(vertex_shader);
	unsigned int fs = compile_shader(fragment_shader);

	unsigned int shader_program;
	shader_program = glCreateProgram();

	glAttachShader(shader_program, vs);
	glAttachShader(shader_program, fs);
	glLinkProgram(shader_program);

	return shader_program;
}
