#include "cameras/orthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(float viewHeight, float aspectRatio, float nearPlane,
	float farPlane, const ShaderPrograms& shaderPrograms) :
	Camera{aspectRatio, nearPlane, farPlane, shaderPrograms},
	m_gui{*this},
	m_viewHeight{viewHeight}
{
	updateProjectionMatrix();
}

void OrthographicCamera::updateGUI()
{
	m_gui.update();
}

float OrthographicCamera::getViewHeight() const
{
	return m_viewHeight;
}

void OrthographicCamera::setViewHeight(float viewHeight)
{
	m_viewHeight = viewHeight;
	updateProjectionMatrix();
}

void OrthographicCamera::zoom(float zoom)
{
	m_radius /= zoom;
	updateViewMatrix();

	m_viewHeight /= zoom;
	updateProjectionMatrix();
}

void OrthographicCamera::updateProjectionMatrix()
{
	float viewWidth = m_viewHeight * m_aspectRatio;
	m_projectionMatrix =
	{
		2 / viewWidth, 0, 0, 0,
		0, 2 / m_viewHeight, 0, 0,
		0, 0, -2 / (m_farPlane - m_nearPlane), 0,
		0, 0, -(m_farPlane + m_nearPlane) / (m_farPlane - m_nearPlane), 1
	};
}
