#include "game.hpp"
#include "graphics.hpp"
#include "nodes/cube.hpp"
#include "nodes/quad.hpp"

#include "gifdec/gifdec.h"

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
	quad3->texture = "assets/tumblr.gif";
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

	for (size_t i = 0; i < this->nodes.size(); i++) {
		if (std::dynamic_pointer_cast<Quad>(this->nodes[i])) {
			std::dynamic_pointer_cast<Quad>(this->nodes[i])->draw_ui();
		}
	}


	graphics::render();
}

Game::~Game() {

}

void Game::load_texture(std::string path) {
	if (path.substr(path.find_last_of(".") + 1) == "gif") {
		gd_GIF *gif = gd_open_gif(realpath(path.c_str(), NULL));
		if (gif) {
			game::Animation animation = {gif->width, gif->height};

			char *buffer = (char*)malloc(gif->width * gif->height * 3);
			while (gd_get_frame(gif)) {
				gd_render_frame(gif, (uint8_t*)buffer);

				// Create texture
				unsigned int id;
				glGenTextures(1, &id);
				glBindTexture(GL_TEXTURE_2D, id);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, gif->width, gif->height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);

				game::TextureFrame frame = {id, std::chrono::duration<double>(gif->gce.delay / 100.0)};
				animation.frames.push_back(frame);
			}

			this->animations[path] = animation;

			// Free stuff
			free(buffer);
			gd_close_gif(gif);
		}
	}
}
