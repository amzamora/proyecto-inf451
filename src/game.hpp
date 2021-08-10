#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <chrono>

#include "graphics.hpp"

#include <iostream>

namespace game {
	struct Input {
		bool mouse_button_left_pressed = false;
		bool mouse_button_left_just_pressed = false;
		glm::vec2 mouse_pos = glm::vec2(0.0f, 0.0f);
	};

	struct TextureFrame {
		unsigned int id;
		std::chrono::duration<double> delay;
	};

	struct Animation {
		int width;
		int height;
		std::vector<TextureFrame> frames;

		bool playing = false;
		std::chrono::time_point<std::chrono::high_resolution_clock> start;
		int current_frame = 0;

		void play() {
			this->start = std::chrono::high_resolution_clock::now();
			this->playing = true;
		}

		void advance() {
			auto elapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - this->start);
			if (elapsed > this->frames[this->current_frame].delay) {
				this->current_frame = (this->current_frame + 1) % this->frames.size();
				this->start = std::chrono::high_resolution_clock::now();
			}
		}
	};

	struct Node {
		std::string name = "";
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

	game::Input input;
	std::vector<std::shared_ptr<game::Node>> nodes;
	std::unordered_map<std::string, game::Animation> animations;
	bool object_being_dragged = false;
	bool quad_selected = false;
	// std::unordered_map<std::string, Font> fonts;
	// std::unordered_map<std::string, Sound> sound_effects;
	// std::unordered_map<std::string, Texture2D> textures;
	// std::unordered_map<std::string, std::pair<std::string, int>> sprites;

	void update(GLFWwindow *window);
	void draw();

	void load_texture(std::string path);
	void randomize_gifs();

private:
	Game();
	~Game();
};

#endif
