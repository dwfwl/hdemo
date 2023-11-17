#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

struct VAO
{
	uint32_t handle;
};

inline void vao_create(std::unique_ptr<VAO>& self)
{
	glGenVertexArrays(1, &self->handle);
}

inline void vao_bind(const std::unique_ptr<VAO>& self)
{
	glBindVertexArray(self->handle);
}

inline void vao_attr(const std::unique_ptr<VAO>& self, int index, uint32_t size, GLenum type, GLsizei stride, size_t offset)
{
	vao_bind(self);
	glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(index);
}

inline void vao_unbind(const std::unique_ptr<VAO>& self)
{
	glBindVertexArray(0);
}