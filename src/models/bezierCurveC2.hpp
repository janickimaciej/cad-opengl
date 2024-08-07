#pragma once

#include "guis/modelGUIs/modelGUI.hpp"
#include "guis/modelGUIs/bezierCurveC2GUI.hpp"
#include "meshes/polylineMesh.hpp"
#include "models/curveBase.hpp"
#include "models/model.hpp"
#include "models/point.hpp"
#include "shaderProgram.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <utility>
#include <vector>

class BezierCurveC2 : public Model
{
public:
	static std::pair<std::unique_ptr<BezierCurveC2>, std::vector<std::unique_ptr<Point>>>
		create(const ShaderProgram& curveShaderProgram, const ShaderProgram& polylineShaderProgram,
		const ShaderProgram& pointShaderProgram, const std::vector<Point*>& boorPoints);
	static std::vector<std::unique_ptr<Point>> createBezierPoints(
		const ShaderProgram& pointShaderProgram, const std::vector<Point*> boorPoints);
	static void updateBezierPoints(const std::vector<Point*>& bezierPoints,
		const std::vector<Point*> boorPoints);

	virtual void render() const override;
	virtual void updateGUI() override;

	virtual void setPos(const glm::vec3&) override;
	virtual void setScreenPos(const glm::vec2&, const glm::mat4&, const glm::ivec2&) override;

	int getPointCount() const;
	std::vector<std::unique_ptr<Point>> addPoints(const std::vector<Point*>& points);
	void deleteBoorPoint(int index);

	std::vector<std::string> getPointNames() const;

	bool getRenderPolyline() const;
	void setRenderPolyline(bool renderPolyline);

private:
	static int m_count;
	
	const ShaderProgram& m_curveShaderProgram;
	const ShaderProgram& m_polylineShaderProgram;
	const ShaderProgram& m_pointShaderProgram;
	BezierCurveC2GUI m_gui;

	unsigned int m_VBOCurve{};
	unsigned int m_VAOCurve{};
	std::unique_ptr<PolylineMesh> m_boorPolylineMesh{};
	std::unique_ptr<PolylineMesh> m_bezierPolylineMesh{};

	std::vector<Point*> m_boorPoints{};
	std::vector<Point*> m_bezierPoints{};
	std::vector<std::shared_ptr<Point::Callback>> m_moveNotificationsBoor{};
	std::vector<std::shared_ptr<Point::Callback>> m_destroyNotificationsBoor{};
	std::vector<std::shared_ptr<Point::Callback>> m_moveNotificationsBezier{};
	bool firstCall = true;

	CurveBase m_base = CurveBase::boor;
	bool m_renderPolyline = true;

	BezierCurveC2(const ShaderProgram& curveShaderProgram,
		const ShaderProgram& polylineShaderProgram, const ShaderProgram& pointShaderProgram,
		const std::vector<Point*>& boorPoints, const std::vector<Point*>& bezierPoints);

	void createCurveMesh();
	void createBoorPolylineMesh();
	void createBezierPolylineMesh();

	virtual void updateShaders() const override;
	void updateWithBezierPoint(int index);
	void updateBezierPoints() const;
	void updateMeshes();

	void updatePos();
	void updateCurveMesh();
	void updateBoorPolylineMesh();
	void updateBezierPolylineMesh();

	void deleteBezierPoint(int index);

	void registerForNotificationsBoor(Point* point);
	void registerForNotificationsBoor(const std::vector<Point*>& points);
	void registerForNotificationsBezier(Point* point);
	void registerForNotificationsBezier(const std::vector<Point*>& points);

	void renderCurve() const;
	void renderBoorPolyline() const;
	void renderBezierPolyline() const;

	static std::vector<glm::vec3> pointsToVertices(const std::vector<Point*> points);
};
