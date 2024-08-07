#include "canvas.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <array>

static constexpr int vertexCount = 6;

Canvas::Canvas()
{
	static const std::array<glm::vec3, vertexCount> vertices
	{{
		{-1.0f, -1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f},
		{-1.0f, 1.0f, 0.0f},
		{-1.0f, -1.0f, 0.0f},
		{1.0f, -1.0f, 0.0f},
		{1.0f, 1.0f, 0.0f}
	}};

	glGenBuffers(1, &m_VBO);
	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(glm::vec3)),
		vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), static_cast<void*>(0));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Canvas::render() const
{
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexCount));
	glBindVertexArray(0);
}
