#include "game.hpp"
#include "graphics.hpp"
#include "nodes/cube.hpp"
#include "nodes/quad.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Game::Game() {
	std::shared_ptr<Cube> cube = std::make_shared<Cube>();
	cube->angle[1] = -45.0f;
	this->nodes.push_back(std::dynamic_pointer_cast<game::Node>(cube));

	std::shared_ptr<Quad> quad1 = std::make_shared<Quad>(glm::vec2(-350.0f, -250.0f));
	quad1->name = "Quad 1";
	quad1->color = glm::vec3(0.0f, 1.0f, 1.0f);
	this->nodes.push_back(std::dynamic_pointer_cast<game::Node>(quad1));

	std::shared_ptr<Quad> quad2 = std::make_shared<Quad>(glm::vec2(-250.0f, -250.0f));
	quad2->name = "Quad 2";
	quad2->color = glm::vec3(1.0f, 1.0f, 0.0f);
	this->nodes.push_back(std::dynamic_pointer_cast<game::Node>(quad2));

	std::shared_ptr<Quad> quad3 = std::make_shared<Quad>(glm::vec2(-150.0f, -250.0f));
	quad3->name = "Quad 3";
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

	this->input.mouse_button_left_just_pressed = false;
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

void Game::load_texture(std::string path) {
	// Load image
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);

	//printf("%s\n", path.c_str());
	unsigned char *data = stbi_load(realpath(path.c_str(), NULL), &width, &height, &nrChannels, 0);

	// Create texture
	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	game::Texture texture = {id, width, height};
	this->textures[path] = texture;

	// Free stuff
	stbi_image_free(data);
}
