#pragma once

#include <Core/Layer.h>
#include <Render/Shader.h>

class Polygon : public Core::Layer
{
public:
	Polygon();
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnRender() override;
	void OnImGuiRender() override;

private:
	Render::Shader _shader;
	Render::VertexArray _vao;
};
