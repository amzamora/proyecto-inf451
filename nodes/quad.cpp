#include "quad.hpp"

void Quad::update(GLFWwindow *window) {

}

void Quad::draw() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(this->position[0] + 100.0f, this->position[1] + 100.f, 0.0f));
	model = glm::scale(model, glm::vec3(200.0f, 200.f, 1.0f));
	model = glm::rotate(model, glm::radians(this->angle), glm::vec3(0.0f, 0.0f, 1.0f));
	graphics::draw_quad(glm::mat4(1.0f));
}
