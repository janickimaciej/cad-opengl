#include "grid/grid.hpp"

Grid::Grid(float scale) :
	m_scale{scale}
{ }

void Grid::render(const ShaderProgram& shaderProgram, CameraType cameraType) const
{
	updateShaders(shaderProgram, cameraType);
	m_canvas.render();
}

void Grid::updateShaders(const ShaderProgram& shaderProgram, CameraType cameraType) const
{
	shaderProgram.setUniform1f("scale", m_scale);
	shaderProgram.setUniform1i("cameraType", static_cast<int>(cameraType));
}
