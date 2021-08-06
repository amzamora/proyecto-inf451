#include "cube.hpp"

void Cube::update(GLFWwindow *window) {

}

#include <iostream>
void Cube::draw() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, this->position);
	model = glm::rotate(model, glm::radians(this->angle[0]), glm::vec3(0.1f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(this->angle[1]), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(this->angle[2]), glm::vec3(0.0f, 0.0f, 1.0f));
	graphics::draw_cube(model);
}
