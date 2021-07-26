#include "game.hpp"
#include "graphics.hpp"

Game::Game() {
	std::shared_ptr<game::Cube> cube = std::make_shared<game::Cube>(glm::vec3(0.0f, 0.0f, 0.0f));
	cube->angle[1] = -45.0f;
	this->nodes.push_back(std::dynamic_pointer_cast<game::Node>(cube));
}

void Game::update(GLFWwindow *window) {
	glfwPollEvents();

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	for (size_t i = 0; i < this->nodes.size(); i++) {
		this->nodes[i]->update(window);
	}
}

void Game::draw() {
	graphics::clear();

	for (size_t i = 0; i < this->nodes.size(); i++) {
		this->nodes[i]->draw();
	}

	graphics::render();
}

Game::~Game() {

}

void game::Cube::update(GLFWwindow *window) {

}

#include <iostream>
void game::Cube::draw() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(this->angle[0]), glm::vec3(0.1f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(this->angle[1]), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(this->angle[2]), glm::vec3(0.0f, 0.0f, 1.0f));
	graphics::draw_cube(model);
}
