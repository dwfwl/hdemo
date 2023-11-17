#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

struct EBO
{
	uint32_t handle;
};

inline void ebo_create(const std::unique_ptr<EBO>& self)
{
	glGenBuffers(1, &self->handle);
}

inline void ebo_bind(const std::unique_ptr<EBO>& self)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->handle);
}

inline void ebo_buffer(const std::unique_ptr<EBO>& self, std::vector<uint32_t> indices)
{
	ebo_bind(self);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);
}

inline void ebo_unbind(const std::unique_ptr<EBO>& self)
{
	glBindBuffer(0, self->handle);
}
