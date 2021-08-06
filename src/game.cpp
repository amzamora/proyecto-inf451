#include "game.hpp"
#include "graphics.hpp"
#include "nodes/cube.hpp"
#include "nodes/quad.hpp"

#include <iostream>
Game::Game() {
	std::shared_ptr<Cube> cube = std::make_shared<Cube>();
	cube->angle[1] = -45.0f;
	this->nodes.push_back(std::dynamic_pointer_cast<game::Node>(cube));

	std::shared_ptr<Quad> quad = std::make_shared<Quad>();
	quad->angle = -45.0f;
	this->nodes.push_back(std::dynamic_pointer_cast<game::Node>(quad));
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
