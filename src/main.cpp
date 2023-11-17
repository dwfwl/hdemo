#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <iostream>
#include <stdexcept>

#include <PL/EBO.h>
#include <PL/VAO.h>
#include <PL/VBO.h>

#include <Graphics/Shader.h>
#include <Graphics/Texture.h>

#include <Model/Mesh.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define width 700
#define height 700

std::vector<Vertex> vertices = {
	// Front face
	Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0, 1)}, // top left
	Vertex{glm::vec3(-0.5f,-0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0, 0)}, // bottom left
	Vertex{glm::vec3(0.5f,-0.5f, -0.5f),  glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(1, 0)}, // bottom right
	Vertex{glm::vec3(0.5f, 0.5f, -0.5f),  glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(1, 1)}, // top right

	// Back face
	Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(0, 1)}, // top left
	Vertex{glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(0, 0)}, // bottom left
	Vertex{glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(1, 0)}, // bottom right
	Vertex{glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(1, 1)}, // top right

	// Left face
	Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),  glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(0, 1)}, // top front
	Vertex{glm::vec3(-0.5f,-0.5f, 0.5f),  glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(0, 0)}, // bottom front
	Vertex{glm::vec3(-0.5f,-0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(1, 0)}, // bottom back
	Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(1, 1)}, // top back

	// Right face
	Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(0, 1)}, // top back
	Vertex{glm::vec3(0.5f,-0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(0, 0)}, // bottom back
	Vertex{glm::vec3(0.5f,-0.5f, 0.5f),  glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(1, 0)}, // bottom front
	Vertex{glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(1, 1)}, // top front

	// Top face
	Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),  glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(0, 1)}, // left back
	Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(0, 0)}, // left front
	Vertex{glm::vec3(0.5f, 0.5f, -0.5f),  glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(1, 0)}, // right front
	Vertex{glm::vec3(0.5f, 0.5f, 0.5f),   glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(1, 1)}, // right back

	// Bottom face
	Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(0, 1)}, // left front
	Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(0, 0)}, // left back
	Vertex{glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(1, 0)}, // right back
	Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),glm::vec2(1, 1)} // right front
};

std::vector<uint32_t> indices = {
	0, 1, 2,  0, 2, 3,    // Front face
	4, 5, 6,  4, 6, 7,    // Back face
	8, 9, 10, 8, 10, 11,  // Left face
	12, 13, 14, 12, 14, 15, // Right face
	16, 17, 18, 16, 18, 19, // Top face
	20, 21, 22, 20, 22, 23  // Bottom face
};

int main(void)
{
	try
	{
		glfwInit();

		GLFWwindow* window = glfwCreateWindow(width, height, "Demo Horror Game", NULL, NULL);
		glfwMakeContextCurrent(window);
		gladLoadGL();

		Texture diff0;
		diff0.type = "texture_diffuse";
		texture_create(diff0, "assets/rock_diff.jpg");
		Texture diff1;
		diff1.type = "texture_specular";
		texture_create(diff1, "assets/rock_norm.png");
		Texture spec0;
		spec0.type = "texture_specular";
		texture_create(spec0, "assets/rock_spec.png");

		Mesh cube(vertices, indices, std::vector<Texture>{diff0, spec0, diff1});

		std::unique_ptr<Shader> shader = std::make_unique<Shader>();
		shader_create(shader, "include/Shaders/main.vert", "include/Shaders/main.frag");

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glm::mat4 model = glm::mat4(1.0f);

			model = glm::rotate(model, glm::radians(sinf(glfwGetTime() * 2) * 150), glm::vec3(1.0f, 1.0f, 0.0f));

			glm::mat4 view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(40.0f), (float)600 / (float)600, 0.1f, 100.0f);

			GLuint modelLoc = glGetUniformLocation(shader->handle, "model");
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

			GLuint viewLoc = glGetUniformLocation(shader->handle, "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

			GLuint projLoc = glGetUniformLocation(shader->handle, "projection");
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

			shader_use(shader);

			cube.draw(shader);

			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		glfwDestroyWindow(window);
		glfwTerminate();

		return 0;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}