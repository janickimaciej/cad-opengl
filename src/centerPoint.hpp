#pragma once

#include "guis/centerPointGUI.hpp"
#include "meshes/pointMesh.hpp"
#include "models/model.hpp"
#include "shaderProgram.hpp"

#include <glm/glm.hpp>

#include <vector>

class CenterPoint
{
public:
	CenterPoint(const ShaderProgram& shaderProgram, const std::vector<Model*>& models);
	void render();
	void updateGUI();

	glm::vec3 getPos() const;
	void setPos(const glm::vec3& pos);

	void rotateX(float angleRad);
	void rotateY(float angleRad);
	void rotateZ(float angleRad);

	void scaleX(float scale);
	void scaleY(float scale);
	void scaleZ(float scale);

private:
	const ShaderProgram& m_shaderProgram;

	const std::vector<Model*>& m_models{};
	CenterPointGUI m_gui;

	PointMesh m_mesh{};

	void rotate(const glm::mat3& rotationMatrix);
	void updateShaders() const;
	static glm::vec3 matrixToEuler(const glm::mat3& rotationMatrix);
};
