#include <iostream>

#include "graphics.hpp"
#include "shader.hpp"
#include "game.hpp"
#include "utilities.hpp"

GLFWwindow* window;
unsigned int width;
unsigned int height;
unsigned int shader_program;
unsigned int shader_program_2d;
unsigned int cube_VAO;
unsigned int plane_VAO;

GLFWwindow* graphics::create_window(int width, int height, const char* title) {
	// Init GLFW
	glfwInit();
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create window
	window = glfwCreateWindow(width, height, "Computación gráfica", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	::width = width;
	::height = height;
	glfwMakeContextCurrent(window);
	glfwSetWindowAspectRatio(window, width, height);

	// Handle input
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			Game::instance().input.mouse_button_left_pressed = true;
		}
		else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
			Game::instance().input.mouse_button_left_pressed = false;
		}
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		Game::instance().input.mouse_pos = glm::vec2(xpos - ::width / 2.0f, ::height / 2.0f - ypos);
	});

	// Load opengl functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}
	// Setup init imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Configure OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);

	// Create shader program
	shader_program = create_shader("shaders/vertex_shader.vs", "shaders/fragment_shader.fs");
	shader_program_2d = create_shader("shaders/2d.vs", "shaders/2d.fs");

	// Load geometry
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	unsigned int VBO;
	glGenVertexArrays(1, &cube_VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(cube_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	float plane_vertices[] = {
		 0.5f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f,
		-0.5f, -0.5f
	};

	unsigned int plane_VBO;
	glGenVertexArrays(1, &plane_VAO);
	glGenBuffers(1, &plane_VBO);

	glBindVertexArray(plane_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, plane_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertices), plane_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return window;
}

void graphics::close() {
	glfwTerminate();
}

void graphics::clear() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void graphics::draw_cube(glm::mat4 model) {
	// Set up transformations
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 1.5f, 2.5f),
					   glm::vec3(0.0f, 0.0f, 0.0f),
					   glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	// Select shader
	glUseProgram(shader_program);

	// Set object color
	glUniform3f(glGetUniformLocation(shader_program, "objectColor"), 1.0f, 1.0f, 1.0f);

	// Pass transformations to shader
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "model"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, &projection[0][0]);

	// Pass light postion and color to shader
	glUniform3f(glGetUniformLocation(shader_program, "lightPos"), -0.2f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(shader_program, "lightColor"), 1.0f, 1.0f, 1.0f);

	// Draw
	glBindVertexArray(cube_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void graphics::draw_quad(std::vector<glm::vec2> vertices, glm::mat4 model, glm::vec3 color) {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Pass vertices to the gpu
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	int concave_point = 0;
	int vertices_size = (int) vertices.size();
	for (int i = 0; i < vertices.size(); i++) {
		glm::vec2 triangle[] = {vertices[(i + 1) % vertices.size()], vertices[(i + 2) % vertices_size], vertices[(i + 3) % vertices_size]};
		if (is_inside_triangle(triangle, vertices[i])) {
			concave_point = i;
		}
	}

	// Put indices in GPU
	size_t n = 6;
	int indices[n] = {
		concave_point, (concave_point + 1) % vertices_size,  (concave_point + 2) % vertices_size,
		(concave_point + 2) % vertices_size, (concave_point + 3) % vertices_size, (concave_point + 4) % vertices_size
	};

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * n, &indices[0], GL_STATIC_DRAW);

	// Make projection matrix
	glm::mat4 projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);

	// Select shader
	glUseProgram(shader_program_2d);

	// Pase transformatiosn to shader
	glm::mat4 real_model = glm::mat4(1.0f);
	real_model = glm::translate(real_model, glm::vec3((width / 2.0f), (height / 2.0f), 0.0f));
	real_model = real_model * model;
	glUniformMatrix4fv(glGetUniformLocation(shader_program_2d, "model"), 1, GL_FALSE, &real_model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader_program_2d, "projection"), 1, GL_FALSE, &projection[0][0]);

	// Set object color
	glUniform3f(glGetUniformLocation(shader_program_2d, "objectColor"), color[0], color[1], color[2]);

	// Draw
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void graphics::render() {
	glfwSwapBuffers(window);
}
