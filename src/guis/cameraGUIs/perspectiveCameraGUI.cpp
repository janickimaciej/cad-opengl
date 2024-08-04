#include "guis/cameraGUIs/perspectiveCameraGUI.hpp"

#include "cameras/perspectiveCamera.hpp"

#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <algorithm>
#include <string>

PerspectiveCameraGUI::PerspectiveCameraGUI(PerspectiveCamera& camera) :
	m_camera{camera}
{ }

void PerspectiveCameraGUI::update()
{
	static const std::string suffix = "##orthographicCamera";

	getValues();

	ImGui::InputInt(("FOV Y" + suffix).c_str(), &m_fovYDeg, 1, 1);
	m_fovYDeg = std::clamp(m_fovYDeg, 20, 160);

	setValues();
}

void PerspectiveCameraGUI::getValues()
{
	m_fovYDeg = static_cast<int>(m_camera.getFOVYDeg());
}

void PerspectiveCameraGUI::setValues()
{
	m_camera.setFOVYDeg(static_cast<float>(m_fovYDeg));
}
