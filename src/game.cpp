#include "game.hpp"
#include "graphics.hpp"
#include "nodes/cube.hpp"
#include "nodes/quad.hpp"

#include <iostream>
Game::Game() {
	std::shared_ptr<Cube> cube = std::make_shared<Cube>();
	cube->angle[1] = -45.0f;
	this->nodes.push_back(std::dynamic_pointer_cast<game::Node>(cube));

	std::shared_ptr<Quad> quad1 = std::make_shared<Quad>(glm::vec2(-350.0f, -250.0f));
	quad1->color = glm::vec3(0.0f, 1.0f, 1.0f);
	this->nodes.push_back(std::dynamic_pointer_cast<game::Node>(quad1));

	std::shared_ptr<Quad> quad2 = std::make_shared<Quad>(glm::vec2(-250.0f, -250.0f));
	quad2->color = glm::vec3(1.0f, 1.0f, 0.0f);
	this->nodes.push_back(std::dynamic_pointer_cast<game::Node>(quad2));

	std::shared_ptr<Quad> quad3 = std::make_shared<Quad>(glm::vec2(-150.0f, -250.0f));
	quad3->color = glm::vec3(1.0f, 0.0f, 1.0f);
	this->nodes.push_back(std::dynamic_pointer_cast<game::Node>(quad3));
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
