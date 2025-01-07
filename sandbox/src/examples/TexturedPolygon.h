#pragma once

#include <Core/Layer.h>
#include <Render/Shader.h>

class TexturedPolygon : public Core::Layer
{
public:
	TexturedPolygon();
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnRender() override;
	void OnImGuiRender() override;

private:
	Render::Shader _shader;
	Render::VertexArray _vao;
};
