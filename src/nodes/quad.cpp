#include "quad.hpp"

void Quad::update(GLFWwindow *window) {
	glm::vec2 mouse_pos = Game::instance().input.mouse_pos;

	if (!this->dragged && !Game::instance().object_being_dragged) {
		if (Game::instance().input.mouse_button_left_pressed) {
			if (fabs(this->position[0] - mouse_pos[0]) <= (this->width / 2.0f) && fabs(this->position[1] - mouse_pos[1]) <= (this->height / 2.0f)) {
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
	model = glm::scale(model, glm::vec3(this->width, this->height, 1.0f));
	graphics::draw_quad(model, this->color);
}
