#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 tex;
};

struct VBO
{
	uint32_t handle;
};

inline void vbo_create(const std::unique_ptr<VBO>& self)
{
	glGenBuffers(1, &self->handle);
}

inline void vbo_bind(const std::unique_ptr<VBO>& self)
{
	glBindBuffer(GL_ARRAY_BUFFER, self->handle);
}

inline void vbo_buffer(const std::unique_ptr<VBO>& self, std::vector<Vertex> vertices)
{
	vbo_bind(self);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

inline void vbo_unbind(const std::unique_ptr<VBO>& self)
{
	glBindBuffer(0, self->handle);
}