#pragma once

#include "guis/cameraGUIs/cameraGUI.hpp"
#include "guis/cameraGUIs/orthographicCameraGUI.hpp"
#include "cameras/camera.hpp"
#include "shaderPrograms.hpp"

class OrthographicCamera : public Camera
{
public:
	OrthographicCamera(float viewWidth, float aspectRatio, float nearPlane, float farPlane,
		const ShaderPrograms& shaderPrograms);
	virtual CameraGUI& getGUI() override;
	float getViewWidth() const;
	void setViewWidth(float viewWidth);
	virtual void zoom(float zoom) override;

protected:
	virtual void updateProjectionMatrix() override;

private:
	OrthographicCameraGUI m_gui;

	float m_viewWidth{};
};