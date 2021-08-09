#include "game.hpp"
#include "graphics.hpp"
#include "nodes/cube.hpp"
#include "nodes/quad.hpp"

Game::Game() {
	std::shared_ptr<Cube> cube = std::make_shared<Cube>();
	cube->angle[1] = -45.0f;
	this->nodes.push_back(std::dynamic_pointer_cast<game::Node>(cube));

	std::shared_ptr<Quad> quad1 = std::make_shared<Quad>(glm::vec2(-350.0f, -250.0f));
	quad1->color = glm::vec3(0.0f, 1.0f, 1.0f);
	this->nodes.push_back(std::dynamic_pointer_cast<game::Node>(quad1));

	std::shared_ptr<Quad> quad2 = std::make_shared<Quad>(glm::vec2(-250.0f, -250.0f));
	quad2->color = glm::vec3(1.0f, 1.0f, 0.0f);
	this->nodes.push_back(std::dynamic_pointer_cast<game::Node>(quad2));

	std::shared_ptr<Quad> quad3 = std::make_shared<Quad>(glm::vec2(-150.0f, -250.0f));
	quad3->color = glm::vec3(1.0f, 0.0f, 1.0f);
	this->nodes.push_back(std::dynamic_pointer_cast<game::Node>(quad3));
}

void Game::update(GLFWwindow *window) {
	glfwPollEvents();

	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	for (size_t i = 0; i < this->nodes.size(); i++) {
		this->nodes[i]->update(window);
	}

	this->input.mouse_button_left_just_pressed = false;
}

void Game::draw() {
	graphics::clear();

	for (size_t i = 0; i < this->nodes.size(); i++) {
		this->nodes[i]->draw();
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static float f = 0.0f;
	static int counter = 0;

	std::shared_ptr<Quad> quad1 = std::dynamic_pointer_cast<Quad>(this->nodes[1]);

	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
	ImGui::ColorEdit3("Quad 1 color", (float*)&(quad1->color.r)); // Edit 3 floats representing a color

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	graphics::render();
}

Game::~Game() {

}
