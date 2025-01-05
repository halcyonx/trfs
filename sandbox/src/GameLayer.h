#pragma once

#include <Core/Layer.h>
#include <Render/Shader.h>
#include <Render/Texture.h>

class GameLayer : public Core::Layer
{
public:
	using SetLayerFunc = std::function<void(std::string_view)>;
	explicit GameLayer(SetLayerFunc&& func);

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnRender() override;
	void OnImGuiRender() override;

private:
	void DrawOverlay();
	void DrawRightOverlay();

private:
	Render::Shader _shader;
	SetLayerFunc _setExampleLayerFunc;
};
