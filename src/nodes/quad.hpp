#ifndef QUAD_HPP
#define QUAD_HPP

#include "../game.hpp"

struct Quad : game::Node2d {
	virtual void update(GLFWwindow *window);
	virtual void draw();
	glm::vec3 color;
	bool dragged = false;
	glm::vec2 drag_position;
	glm::vec2 vertices[4] = {glm::vec2(-50.0f, 50.0f), glm::vec2(-50.0f, -50.0f), glm::vec2(50.0f, -50.0f), glm::vec2(50.0f, 50.0f)};

	Quad() : Node2d() {}
	Quad(glm::vec2 position) : Node2d(position) {}
	~Quad() {}
};

#endif
