#include "quad.hpp"

void Quad::update(GLFWwindow *window) {

}

void Quad::draw() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(this->position[0], this->position[1], 0.0f));
	model = glm::rotate(model, glm::radians(this->angle), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(this->width, this->height, 1.0f));
	graphics::draw_quad(model, this->color);
}
