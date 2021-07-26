#include <iostream>

#include "shader.hpp"
#include "graphics.hpp"

#define WIDTH 800
#define HEIGHT 600

// Prototypes
// ----------
void process_input(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Implementations
// ---------------
int main() {
	// Create window
	GLFWwindow* window = graphics::create_window(800, 600, "Proyecto");

	// Main loop
	while(!glfwWindowShouldClose(window)) {
		// Keayboard input
		process_input(window);

		// Clear
		graphics::clear();

		// Draw cube
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		graphics::draw_cube(model);

		// Render
		graphics::render();

		// Get events
		glfwPollEvents();
	}

	// Close glfw
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
