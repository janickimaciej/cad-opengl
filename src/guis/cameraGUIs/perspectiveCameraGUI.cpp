#include "guis/cameraGUIs/perspectiveCameraGUI.hpp"

#include "cameras/perspectiveCamera.hpp"

#include <imgui/imgui.h>

#include <algorithm>
#include <string>

PerspectiveCameraGUI::PerspectiveCameraGUI(PerspectiveCamera& camera) :
	m_camera{camera}
{ }

void PerspectiveCameraGUI::update()
{
	static const std::string suffix = "##orthographicCamera";

	int fovYDeg = static_cast<int>(m_camera.getFOVYDeg());
	ImGui::InputInt(("FOV Y" + suffix).c_str(), &fovYDeg, 1, 1);
	fovYDeg = std::clamp(fovYDeg, 20, 160);
	m_camera.setFOVYDeg(static_cast<float>(fovYDeg));
}
