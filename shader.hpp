#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <string>

unsigned int create_shader(std::string vertex_shader, std::string fragment_shader);

#endif
