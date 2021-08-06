#include <iostream>

#include "game.hpp"

// Prototypes
// ----------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Implementations
// ---------------
int main() {
	// Create window
	GLFWwindow* window = graphics::create_window(800, 600, "Proyecto");

	// Main loop
	while(!glfwWindowShouldClose(window)) {
		Game::instance().update(window);
		Game::instance().draw();
	}

	// Close glfw
	glfwTerminate();

	return 0;
}
