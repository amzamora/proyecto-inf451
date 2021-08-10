#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_stdlib.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>

namespace graphics {
	GLFWwindow* create_window(int width, int height, const char* title);
	void close();
	void clear();
	void draw_cube(glm::mat4 model);
	void draw_quad(std::vector<glm::vec2> vertices, glm::mat4 model, glm::vec3 color);
	void draw_quad(std::vector<glm::vec2> vertices, glm::mat4 model, std::string texture_path);
	void render();
}

#endif
