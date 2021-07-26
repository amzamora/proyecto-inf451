#ifndef CUBE_HPP
#define CUBE_HPP

#include "../game.hpp"

struct Cube : game::Node {
	virtual void update(GLFWwindow *window);
	virtual void draw();

	Cube() : Node() {}
	Cube(glm::vec3 position) : Node(position) {}
	~Cube() {}
};

#endif
