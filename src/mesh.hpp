#pragma once

#include "render_mode.hpp"
#include "vertex.hpp"

#include <cstddef>
#include <string>
#include <vector>

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indicesWireframe,
		const std::vector<unsigned int>& indicesSolid);
	void render(RenderMode renderMode) const;
	~Mesh();
	
private:
	std::size_t m_indexCountWireframe{};
	std::size_t m_indexCountSolid{};
	unsigned int m_VBO{};
	unsigned int m_EBOWireframe{};
	unsigned int m_EBOSolid{};
	unsigned int m_VAOWireframe{};
	unsigned int m_VAOSolid{};

	void createBuffersWireframe(const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices);
	void createBuffersSolid(const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices);
};
