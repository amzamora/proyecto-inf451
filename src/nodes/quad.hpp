#ifndef QUAD_HPP
#define QUAD_HPP

#include "../game.hpp"

struct Quad : game::Node2d {
	virtual void update(GLFWwindow *window);
	virtual void draw();
	float width = 100.0f;
	float height = 100.0f;
	glm::vec3 color;
	bool dragged = false;
	glm::vec2 drag_position;

	Quad() : Node2d() {}
	Quad(glm::vec2 position) : Node2d(position) {}
	~Quad() {}
};

#endif
