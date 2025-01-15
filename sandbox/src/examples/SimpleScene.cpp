#include "SimpleScene.h"

#include <Math/Transform.h>
#include <Render/RenderFunc.h>
#include <Render/RenderUtils.h>
#include <Core/Subsystems.h>
#include <Core/Application.h>

static float* GetCubeVertices();
static size_t GetCubeVerticesSize();

SimpleScene::SimpleScene()
	: Core::Layer("SimpleScene")
{
}

void SimpleScene::OnAttach()
{
	SetupScene();
}

void SimpleScene::OnDetach()
{
}

void SimpleScene::OnUpdate(float dt)
{
	_camera.OnUpdate(dt);
}

void SimpleScene::OnRender()
{
	Render::DepthTestGuard depthTestGuard;
	Render::ClearColor(0.3, 0.4, 0.5, 1.0);
	Render::Clear();

	_shader.Bind();
	_shader.BindTexture2D(0, _texture0);
	_shader.BindTexture2D(1, _texture1);

	const auto [windowWidth, windowHeight] = Core::Application::GetWindowSize();
	const float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
	const auto time = Core::GetTimeManager().GetAppTime();
	// Draw quad
	{
		Math::Mat4 modelMatrix { 1.0f };
		modelMatrix = Math::Transform::Translate(modelMatrix, Math::Vec3(0.5f, -0.5f, 0.0f));
		modelMatrix = Math::Transform::Rotate(modelMatrix, Math::Radians(-55.0f), Math::Vec3(1.0f, 0.0f, 0.0f));
		modelMatrix = Math::Transform::Scale(modelMatrix, { 2.5f, 2.5f, 1.0f });

		Math::Mat4 viewMatrix { 1.0f };
		viewMatrix = Math::Transform::Translate(viewMatrix, Math::Vec3(0.0f, 0.0f, -3.0f));

		Math::Mat4 projectionMatrix { 1.0f };
		projectionMatrix = Math::Perspective(Math::Radians(45.0f), aspectRatio, 0.1f, 100.0f);

		Math::Mat4 transform = projectionMatrix * viewMatrix * modelMatrix;
		_shader.SetUniform("transform", transform);
	}
	Render::DrawIndexed(_vao);

	//	Draw box
	{
		Math::Mat4 modelMatrix { 1.0f };
		modelMatrix = Math::Transform::Rotate(modelMatrix, Math::Radians(time * 50.0f), Math::Vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = Math::Transform::Scale(modelMatrix, { 0.5f, 0.5f, 0.5f });

		Math::Mat4 viewMatrix = _camera.GetViewMatrix();

		Math::Mat4 projectionMatrix { 1.0f };
		projectionMatrix = Math::Perspective(Math::Radians(45.0f), aspectRatio, 0.1f, 100.0f);

		Math::Mat4 transform = projectionMatrix * viewMatrix * modelMatrix;
		_shader.SetUniform("transform", transform);
	}

	Render::DrawPrimitives(_vaoCube, Render::PrimitiveType::Triangles, 36);
	_shader.Unbind();
}

void SimpleScene::OnImGuiRender()
{
}

void SimpleScene::SetupScene()
{
	_shader = Core::GetAssetManager().LoadShader("textured_transform");
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

	Render::BufferLayout layout({ { "position", Render::RenderType::Float3 },
		{ "color", Render::RenderType::Float3 },
		{ "texCoord", Render::RenderType::Float2 } });

	vb.SetLayout(layout);

	// quad
	_vao.AddVertexBuffer(std::move(vb));
	_vao.SetIndexBuffer(std::move(eb));

	// cube
	Render::VertexBuffer vbCube(GetCubeVertices(), GetCubeVerticesSize());
	vbCube.SetLayout(layout);
	_vaoCube.AddVertexBuffer(std::move(vbCube));

	_camera.SetPosition({ 0.0f, 0.0f, 3.0f });
}

static float cubeVertices[] = {
	// positions		  // colors		   // texture coords
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

static float* GetCubeVertices()
{
	return cubeVertices;
}

static size_t GetCubeVerticesSize()
{
	return sizeof(cubeVertices);
}
