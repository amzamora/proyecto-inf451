#ifndef QUAD_HPP
#define QUAD_HPP

#include "../game.hpp"

struct Quad : game::Node2d {
	virtual void update(GLFWwindow *window);
	virtual void draw();
	glm::vec3 color;
	std::string texture = "";
	bool dragged = false;
	int dragged_vertex = -1;
	glm::vec2 drag_position;
	std::vector<glm::vec2> vertices = {glm::vec2(-50.0f, 50.0f), glm::vec2(-50.0f, -50.0f), glm::vec2(50.0f, -50.0f), glm::vec2(50.0f, 50.0f)};
	bool selected = false;

	Quad() : Node2d() {}
	Quad(glm::vec2 position) : Node2d(position) {}
	~Quad() {}

	void draw_ui();

private:
	int is_mouse_on_vertex(glm::vec2 mouse_pos);
};

#endif
