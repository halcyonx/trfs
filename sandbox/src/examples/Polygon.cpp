#include "Polygon.h"
#include <Core/Subsystems.h>
#include <Render/RenderFunc.h>

Polygon::Polygon()
	: Core::Layer("Polygon")
{
}

void Polygon::OnAttach()
{
	_shader = Core::GetAssetManager().LoadShader("standard");

	Render::VertexBuffer vb({
		// positions		  // colors		   // texture coords
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // top left
	});

	Render::IndexBuffer eb({
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	});

	Render::BufferLayout layout({ { "aPos", Render::RenderType::Float3 },
		{ "aColor", Render::RenderType::Float3 },
		{ "aTexCoord", Render::RenderType::Float2 } });

	vb.SetLayout(std::move(layout));

	_vao.AddVertexBuffer(std::move(vb));
	_vao.SetIndexBuffer(std::move(eb));
}

void Polygon::OnDetach()
{
}

void Polygon::OnUpdate(float dt)
{
}

void Polygon::OnRender()
{
	Render::ClearColor(0.3, 0.4, 0.5, 1.0);
	Render::Clear();

	_shader.Bind();
	//	Render::DrawQuad();
	Render::DrawIndexed(_vao);
	_shader.Unbind();
}

void Polygon::OnImGuiRender()
{
}
