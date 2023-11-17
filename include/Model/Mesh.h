#include <vector>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <PL/EBO.h>
#include <PL/VAO.h>
#include <PL/VBO.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>

class Mesh
{
public:
	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;
	std::vector<Texture> m_textures;

	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures) 
		:m_vertices(vertices), m_indices(indices), m_textures(textures)
	{
		setupMesh();
	}

	void draw(std::unique_ptr<Shader>& shader)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		for (unsigned int i = 0; i < m_textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = m_textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);

			glUniform1i(glGetUniformLocation(shader->handle, ("material." + name + number).c_str()), i);
			glBindTexture(GL_TEXTURE_2D, m_textures[i].handle);
		}
		glActiveTexture(GL_TEXTURE0);

		// draw mesh
		vao_bind(vao);
		glDrawElements(GL_TRIANGLES, m_indices.size() * sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

private:
	std::unique_ptr<VAO> vao = std::make_unique<VAO>();
	std::unique_ptr<VBO> vbo = std::make_unique<VBO>();
	std::unique_ptr<EBO> ebo = std::make_unique<EBO>();

	void setupMesh();
};

void Mesh::setupMesh()
{
	vao_create(vao);
	vbo_create(vbo);
	ebo_create(ebo);

	vao_bind(vao);
	vbo_buffer(vbo, m_vertices);
	ebo_buffer(ebo, m_indices);

	vao_attr(vao, 0, 3, GL_FLOAT, sizeof(Vertex), 0);
	vao_attr(vao, 1, 3, GL_FLOAT, sizeof(Vertex), (3 * sizeof(float)));
	vao_attr(vao, 2, 2, GL_FLOAT, sizeof(Vertex), (6 * sizeof(float)));

	vao_unbind(vao);
}