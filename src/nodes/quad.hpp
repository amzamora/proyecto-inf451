#ifndef QUAD_HPP
#define QUAD_HPP

#include "../game.hpp"

struct Quad : game::Node2d {
	virtual void update(GLFWwindow *window);
	virtual void draw();

	Quad() : Node2d() {}
	Quad(glm::vec2 position) : Node2d(position) {}
	~Quad() {}
};

#endif
