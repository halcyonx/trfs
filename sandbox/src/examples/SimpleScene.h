#pragma once

#include <Core/Layer.h>
#include <Render/Shader.h>
#include <Render/Camera.h>

class SimpleScene : public Core::Layer
{
public:
	SimpleScene();
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnRender() override;
	void OnImGuiRender() override;

private:
	void SetupScene();

private:
	Render::Shader _shader;
	Render::Texture _texture0;
	Render::Texture _texture1;
	Render::Texture _textureWall;
	Render::VertexArray _vao;
	Render::VertexArray _vaoCube;
	Render::Camera _camera;
};
