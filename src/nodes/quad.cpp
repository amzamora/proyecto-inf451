#include "quad.hpp"
#include "../utilities.hpp"

void Quad::update(GLFWwindow *window) {
	glm::vec2 mouse_pos = Game::instance().input.mouse_pos;
	if (!this->dragged && !Game::instance().object_being_dragged) {
		if (Game::instance().input.mouse_button_left_pressed) {
			if (glm::distance(mouse_pos, this->vertices[0] + this->position) < 10.0f) {
				this->dragged = true;
				this->dragged_vertex = 0;
				Game::instance().object_being_dragged = true;

			}
			else if (glm::distance(mouse_pos, this->vertices[1] + this->position) < 10.0f) {
				this->dragged = true;
				this->dragged_vertex = 1;
				Game::instance().object_being_dragged = true;
			}
			else if (glm::distance(mouse_pos, this->vertices[2] + this->position) < 10.0f) {
				this->dragged = true;
				this->dragged_vertex = 2;
				Game::instance().object_being_dragged = true;
			}
			else if (glm::distance(mouse_pos, this->vertices[3] + this->position) < 10.0f) {
				this->dragged = true;
				this->dragged_vertex = 3;
				Game::instance().object_being_dragged = true;
			}
			else if (is_inside_quad(&(this->vertices[0]), mouse_pos - this->position)) {
				this->drag_position = glm::vec2(this->position[0] - mouse_pos[0], this->position[1] - mouse_pos[1]);
				this->dragged = true;
				Game::instance().object_being_dragged = true;
			}
		}
	}
	else if (this->dragged) {
		if (!Game::instance().input.mouse_button_left_pressed) {
			this->dragged = false;
			Game::instance().object_being_dragged = false;
			this->dragged_vertex = -1;
		}
		else if (this->dragged_vertex != -1) {
			this->vertices[this->dragged_vertex] = mouse_pos - this->position + glm::vec2(-3.0f, 7.0f);
		}
		else {
			this->position = mouse_pos + this->drag_position;
		}
	}
}

void Quad::draw() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(this->position[0], this->position[1], 0.0f));
	model = glm::rotate(model, glm::radians(this->angle), glm::vec3(0.0f, 0.0f, 1.0f));
	graphics::draw_quad(this->vertices, model, this->color);
}
