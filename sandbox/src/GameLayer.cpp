#include "GameLayer.h"

#include <Core/Log.h>
#include <Core/Subsystems.h>
#include <Render/RenderFunc.h>

#include <imgui.h>

void GameLayer::DrawOverlay()
{
	static int corner = 0;
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration
									| ImGuiWindowFlags_NoDocking
									| ImGuiWindowFlags_AlwaysAutoResize
									| ImGuiWindowFlags_NoSavedSettings
									| ImGuiWindowFlags_NoFocusOnAppearing
									| ImGuiWindowFlags_NoNav;
	if (corner != -1) {
		const float PAD = 30.0f;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
		ImVec2 work_size = viewport->WorkSize;
		ImVec2 window_pos, window_pos_pivot;
		window_pos.x = (corner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
		window_pos.y = (corner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
		window_pos_pivot.x = (corner & 1) ? 1.0f : 0.0f;
		window_pos_pivot.y = (corner & 2) ? 1.0f : 0.0f;
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		ImGui::SetNextWindowViewport(viewport->ID);
		window_flags |= ImGuiWindowFlags_NoMove;
	}

	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background

	bool* p_open = nullptr;
	if (ImGui::Begin("StatsOverlay", p_open, window_flags)) {
		const int fps = (int)(io.Framerate);
		const int drawCalls = 0; //Render::Renderer::GetDrawCalls();
		ImGui::Text("FPS: %d", fps);
		ImGui::Text("Draw calls: %d", drawCalls);
		ImGui::Separator();
		if (ImGui::IsMousePosValid()) {
			ImGui::Text("Mouse Position: (%.1f,%.1f)", io.MousePos.x, io.MousePos.y);
		}
		else {
			ImGui::Text("Mouse Position: <invalid>");
		}
		if (ImGui::BeginPopupContextWindow()) {
			if (ImGui::MenuItem("Top-left", nullptr, corner == 0)) {
				corner = 0;
			}
			if (ImGui::MenuItem("Top-right", nullptr, corner == 1)) {
				corner = 1;
			}
			if (ImGui::MenuItem("Bottom-left", nullptr, corner == 2)) {
				corner = 2;
			}
			if (ImGui::MenuItem("Bottom-right", nullptr, corner == 3)) {
				corner = 3;
			}
			if (p_open && ImGui::MenuItem("Close")) {
				*p_open = false;
			}
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}

void GameLayer::DrawRightOverlay()
{
	static int corner = 1; // Right side
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration
									| ImGuiWindowFlags_NoDocking
									| ImGuiWindowFlags_AlwaysAutoResize
									| ImGuiWindowFlags_NoSavedSettings
									| ImGuiWindowFlags_NoFocusOnAppearing
									| ImGuiWindowFlags_NoNav;

	const float PAD = 30.0f;
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImVec2 work_pos = viewport->WorkPos;
	ImVec2 work_size = viewport->WorkSize;
	ImVec2 window_pos, window_pos_pivot;
	window_pos.x = work_pos.x + work_size.x - PAD;
	window_pos.y = work_pos.y + PAD;
	window_pos_pivot.x = 1.0f;
	window_pos_pivot.y = 0.0f;
	ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	ImGui::SetNextWindowViewport(viewport->ID);
	window_flags |= ImGuiWindowFlags_NoMove;

	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background

	bool* p_open = nullptr;
	if (ImGui::Begin("ButtonOverlay", p_open, window_flags)) {
		for (const auto& example : _examples) {
			if (ImGui::Button(example.c_str(), { 140, 0 })) {
				_setExampleLayerFunc(example);
			}
		}
		ImGui::End();
	}
}

GameLayer::GameLayer(SetLayerFunc&& func)
	: Layer("GameLayer")
	, _setExampleLayerFunc(std::move(func))
{
	_examples = {
		"Empty", "Polygon"
	};
}

void GameLayer::OnAttach()
{
#if PLATFORM_ANDROID
	ImGuiStyle& style = ImGui::GetStyle();
	style.FramePadding.y = 15;
	style.ItemSpacing.x = 15;
	style.ItemSpacing.x = 7;
	style.ScrollbarSize = 40;
	style.GrabMinSize = 25;

	ImGui::GetIO().FontGlobalScale = 2.0f;
#endif
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate(float dt)
{
}

void GameLayer::OnRender()
{
}

void GameLayer::OnImGuiRender()
{
	DrawOverlay();
	DrawRightOverlay();
	//	ImGui::ShowDemoWindow();
}
