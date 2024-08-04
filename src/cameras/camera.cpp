#include "cameras/camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

Camera::Camera(float aspectRatio, float nearPlane, float farPlane,
	const ShaderPrograms& shaderPrograms) :
	m_aspectRatio{aspectRatio},
	m_nearPlane{nearPlane},
	m_farPlane{farPlane},
	m_shaderPrograms{shaderPrograms}
{
	updateViewMatrix();
}

void Camera::use(const glm::ivec2& windowSize) const
{
	updateShaders(windowSize);
}

glm::mat4 Camera::getMatrix() const
{
	return m_projectionMatrix * glm::inverse(m_viewMatrixInverse);
}

void Camera::addPitch(float pitchRad)
{
	m_pitchRad += pitchRad;

	static constexpr float bound = glm::radians(89.0f);
	if (m_pitchRad < -bound)
	{
		m_pitchRad = -bound;
	}
	if (m_pitchRad > bound)
	{
		m_pitchRad = bound;
	}
	
	updateViewMatrix();	
}

void Camera::addYaw(float yawRad)
{
	m_yawRad += yawRad;
	
	static constexpr float pi = glm::pi<float>();
	while (m_yawRad < -pi)
	{
		m_yawRad += 2 * pi;
	}
	while (m_yawRad >= pi)
	{
		m_yawRad -= 2 * pi;
	}

	updateViewMatrix();
}

void Camera::addRadius(float radius)
{
	m_radius += radius;

	if (m_radius < 0.1f)
	{
		m_radius = 0.1f;
	}
	
	updateViewMatrix();
}

void Camera::moveX(float x)
{
	m_targetPosition += m_radius * glm::mat3{m_viewMatrixInverse} * glm::vec3{x, 0, 0};

	updateViewMatrix();
}

void Camera::moveY(float y)
{
	m_targetPosition += m_radius * glm::mat3{m_viewMatrixInverse} * glm::vec3{0, y, 0};

	updateViewMatrix();
}

void Camera::setAspectRatio(float aspectRatio)
{
	m_aspectRatio = aspectRatio;

	updateProjectionMatrix();
}

void Camera::updateShaders(const glm::ivec2& windowSize) const
{
	glm::mat4 projectionViewMatrix = m_projectionMatrix * glm::inverse(m_viewMatrixInverse);
	glm::mat4 projectionViewMatrixInverse = glm::inverse(projectionViewMatrix);

	m_shaderPrograms.torus.use();
	m_shaderPrograms.torus.setUniform("projectionViewMatrix", projectionViewMatrix);

	m_shaderPrograms.point.use();
	m_shaderPrograms.point.setUniform("projectionViewMatrix", projectionViewMatrix);

	m_shaderPrograms.cursor.use();
	m_shaderPrograms.cursor.setUniform("projectionViewMatrix", projectionViewMatrix);

	m_shaderPrograms.grid.use();
	m_shaderPrograms.grid.setUniform("projectionViewMatrix", projectionViewMatrix);
	m_shaderPrograms.grid.setUniform("projectionViewMatrixInverse",
		projectionViewMatrixInverse);

	m_shaderPrograms.bezierCurvePolyline.use();
	m_shaderPrograms.bezierCurvePolyline.setUniform("projectionViewMatrix",
		projectionViewMatrix);

	m_shaderPrograms.bezierCurve.use();
	m_shaderPrograms.bezierCurve.setUniform("projectionViewMatrix", projectionViewMatrix);
	m_shaderPrograms.bezierCurve.setUniform("windowSize", windowSize);

	m_shaderPrograms.bezierCurveInter.use();
	m_shaderPrograms.bezierCurveInter.setUniform("projectionViewMatrix", projectionViewMatrix);
	m_shaderPrograms.bezierCurveInter.setUniform("windowSize", windowSize);
}

void Camera::updateViewMatrix()
{
	glm::vec3 position = m_targetPosition + m_radius *
		glm::vec3
		{
			-std::cos(m_pitchRad) * std::sin(m_yawRad),
			-std::sin(m_pitchRad),
			std::cos(m_pitchRad) * std::cos(m_yawRad)
		};

	glm::vec3 direction = glm::normalize(position - m_targetPosition);
	glm::vec3 right = glm::normalize(glm::cross(glm::vec3{0, 1, 0}, direction));
	glm::vec3 up = glm::cross(direction, right);


	m_viewMatrixInverse =
	{
		right.x, right.y, right.z, 0,
		up.x, up.y, up.z, 0,
		direction.x, direction.y, direction.z, 0,
		position.x, position.y, position.z, 1
	};
}
