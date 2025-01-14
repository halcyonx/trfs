#include "TexturedPolygon.h"
#include <Core/Subsystems.h>
#include <Render/RenderFunc.h>
#include <Core/Log.h>

TexturedPolygon::TexturedPolygon()
	: Core::Layer("TexturedPolygon")
{
}

void TexturedPolygon::OnAttach()
{
	_shader = Core::GetAssetManager().LoadShader("textured");
	_texture0 = Core::GetAssetManager().LoadTexture("awesomeface");
	_texture1 = Core::GetAssetManager().LoadTexture("container");

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

void TexturedPolygon::OnDetach()
{
}

void TexturedPolygon::OnUpdate(float dt)
{
}

void TexturedPolygon::OnRender()
{
	Render::ClearColor(0.3, 0.4, 0.5, 1.0);
	Render::Clear();

	_shader.Bind();
	_shader.BindTexture2D(0, _texture0);
	_shader.BindTexture2D(1, _texture1);
	Render::DrawIndexed(_vao);
	_shader.Unbind();
}

void TexturedPolygon::OnImGuiRender()
{
}
