#pragma once
class GUIStyle
{
public:
	static void SetupGUIStyle(ImGuiStyle* guiStyleRef) {
		guiStyleRef->FrameRounding = 2.0f;
		guiStyleRef->GrabRounding = guiStyleRef->FrameRounding;
		guiStyleRef->WindowBorderSize = 0.0f;
		guiStyleRef->ScrollbarRounding = 2.0f;

		ImVec4* colors = guiStyleRef->Colors;

		ImVec4 shadeIntervals[11] = {
			ImVec4(0.0f, 0.0f, 0.0f, 1.0f),
			ImVec4(0.1f, 0.1f, 0.1f, 1.0f),
			ImVec4(0.2f, 0.2f, 0.2f, 1.0f),
			ImVec4(0.3f, 0.3f, 0.3f, 1.0f),
			ImVec4(0.4f, 0.4f, 0.4f, 1.0f),
			ImVec4(0.5f, 0.5f, 0.5f, 1.0f),
			ImVec4(0.6f, 0.6f, 0.6f, 1.0f),
			ImVec4(0.7f, 0.7f, 0.7f, 1.0f),
			ImVec4(0.8f, 0.8f, 0.8f, 1.0f),
			ImVec4(0.9f, 0.9f, 0.9f, 1.0f),
			ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
		};

		colors[ImGuiCol_TitleBgCollapsed] = shadeIntervals[1];
		colors[ImGuiCol_TitleBg] = shadeIntervals[2];
		colors[ImGuiCol_TitleBgActive] = shadeIntervals[3];

		colors[ImGuiCol_WindowBg] = shadeIntervals[1];
		colors[ImGuiCol_FrameBg] = shadeIntervals[2];
		colors[ImGuiCol_MenuBarBg] = shadeIntervals[1];

		colors[ImGuiCol_Header] = shadeIntervals[3];
		colors[ImGuiCol_HeaderHovered] = shadeIntervals[4];
		colors[ImGuiCol_HeaderActive] = shadeIntervals[5];

		colors[ImGuiCol_Button] = shadeIntervals[2];
		colors[ImGuiCol_ButtonHovered] = shadeIntervals[3];
		colors[ImGuiCol_ButtonActive] = shadeIntervals[4];

		colors[ImGuiCol_SliderGrab] = shadeIntervals[6];
		colors[ImGuiCol_SliderGrabActive] = shadeIntervals[9];

		colors[ImGuiCol_ScrollbarGrabHovered] = shadeIntervals[1];
		colors[ImGuiCol_ScrollbarGrabActive] = shadeIntervals[2];
		colors[ImGuiCol_ScrollbarGrab] = shadeIntervals[4];
		colors[ImGuiCol_ScrollbarBg] = shadeIntervals[8];
	}
};

