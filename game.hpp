#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>

#include "graphics.hpp"

namespace game {
	struct Node {
		glm::vec3 position;
		glm::vec3 angle;
		glm::vec3 scale;

		Node() : position(glm::vec3(0.0f, 0.0f, 0.0f)), angle(glm::vec3(0.0f, 0.0f, 0.0f)), scale(glm::vec3(0.0f, 0.0f, 0.0f)) {}
		Node(glm::vec3 position) : position(position), angle(glm::vec3(0.0f, 0.0f, 0.0f)), scale(glm::vec3(0.0f, 0.0f, 0.0f)) {}
		virtual void update(GLFWwindow *window) {}
		virtual void draw() {}
		virtual ~Node() {}
	};

	struct Node2d : Node {
		glm::vec2 position;
	 	float angle;
		glm::vec2 scale;

		Node2d() : position(glm::vec2(0.0f, 0.0f)), angle(0.0f), scale(glm::vec2(0.0f, 0.0f)) {}
		Node2d(glm::vec2 position) : position(position), angle(0.0f), scale(glm::vec2(0.0f, 0.0f)) {}
		virtual void update(GLFWwindow *window) {}
		virtual void draw() {}
		virtual ~Node2d() {}
	};
}

class Game {
public:
	static Game& instance() {
		static Game instance;
		return instance;
	}

	std::vector<std::shared_ptr<game::Node>> nodes;
	// std::unordered_map<std::string, Font> fonts;
	// std::unordered_map<std::string, Sound> sound_effects;
	// std::unordered_map<std::string, Texture2D> textures;
	// std::unordered_map<std::string, std::pair<std::string, int>> sprites;

	void update(GLFWwindow *window);
	void draw();

private:
	Game();
	~Game();
};

#endif
