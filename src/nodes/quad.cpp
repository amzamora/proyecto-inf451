#include "quad.hpp"
#include "../utilities.hpp"

void Quad::update(GLFWwindow *window) {
	glm::vec2 mouse_pos = Game::instance().input.mouse_pos;
	if (!this->dragged && !Game::instance().object_being_dragged) {
		if (Game::instance().input.mouse_button_left_just_pressed) {
			if (this->is_mouse_on_vertex(mouse_pos) != -1) {
				this->dragged = true;
				this->dragged_vertex = this->is_mouse_on_vertex(mouse_pos);
				Game::instance().object_being_dragged = true;
			}
			else if (is_inside_quad(&(this->vertices[0]), mouse_pos - this->position)) {
				this->drag_position = glm::vec2(this->position[0] - mouse_pos[0], this->position[1] - mouse_pos[1]);
				this->dragged = true;
				Game::instance().object_being_dragged = true;

				if (Game::instance().quad_selected) {
					for (size_t i = 0; i < Game::instance().nodes.size(); i++) {
						if (std::dynamic_pointer_cast<Quad>(Game::instance().nodes[i])) {
							std::dynamic_pointer_cast<Quad>(Game::instance().nodes[i])->selected = false;
						}
					}
				}
				this->selected = true;
				Game::instance().quad_selected = true;
			}
		}
	}
	else if (this->dragged) {
		if (!Game::instance().input.mouse_button_left_pressed) {
			this->dragged = false;
			Game::instance().object_being_dragged = false;
			this->dragged_vertex = -1;
		}
		else if (this->dragged_vertex != -1) {
			this->vertices[this->dragged_vertex] = mouse_pos - this->position + glm::vec2(-3.0f, 7.0f);
		}
		else {
			this->position = mouse_pos + this->drag_position;
		}
	}
}

void Quad::draw() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(this->position[0], this->position[1], 0.0f));
	model = glm::rotate(model, glm::radians(this->angle), glm::vec3(0.0f, 0.0f, 1.0f));
	if (this->texture != "") {
		graphics::draw_quad(this->vertices, model, this->texture);
	}
	else {
		graphics::draw_quad(this->vertices, model, this->color);
	}

	if (this->selected) {
		this->draw_ui();
	}
}

int Quad::is_mouse_on_vertex(glm::vec2 mouse_pos) {
	for (int i = 0; i < this->vertices.size(); i++) {
		if (glm::distance(mouse_pos, this->vertices[i] + this->position) < 10.0f) {
			return i;
		}
	}
	return -1;
}

void Quad::draw_ui() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin(this->name.c_str());
	ImGui::ColorEdit3("Color", (float*)&(this->color.r));

	ImGui::InputText("Texture path", &(this->texture));

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
