#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace graphics {
	GLFWwindow* create_window(int width, int height, const char* title);
	void close();
	void clear();
	void draw_cube(glm::mat4 model);
	void render();
}

#endif
