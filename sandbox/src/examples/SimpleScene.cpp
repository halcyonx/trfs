#include "SimpleScene.h"

#include "Core/Event/MouseEvent.h"

#include <Math/Transform.h>
#include <Render/RenderFunc.h>
#include <Render/RenderUtils.h>
#include <Core/Subsystems.h>
#include <Core/Application.h>
#include <Core/Log.h>
#include <Core/Event/KeyEvent.h>
#include <Core/Input.h>

// The data for one cube instance
struct CubeInstance
{
	Math::Mat4 modelMatrix;
};

// A house is just a collection of cubes
struct House
{
	std::vector<CubeInstance> cubes;
};

// The entire city is a collection of houses
struct CityModel
{
	std::vector<House> houses;
};

static CityModel gCityModel;

// Create a single house made of a few cubes, placed at "housePos".
House MakeSimpleHouse(const Math::Vec3& housePos)
{
	House house;

	// Start with an identity matrix
	Math::Mat4 baseModel = Math::Transform::Identity();
	// Translate to the house position
	baseModel = Math::Transform::Translate(baseModel, housePos);
	// Scale: 2.0 wide in XZ, 0.5 tall, etc.
	baseModel = Math::Transform::Scale(baseModel, Math::Vec3(2.0f, 0.5f, 2.0f));

	// Add the base cube
	house.cubes.push_back({ baseModel });

	// Second floor: shifted up by 0.5 + 0.25 = ~0.75
	Math::Mat4 secondFloor = Math::Transform::Identity();
	secondFloor = Math::Transform::Translate(secondFloor,
		Math::Vec3(housePos.x, housePos.y + 0.75f, housePos.z));
	secondFloor = Math::Transform::Scale(secondFloor, Math::Vec3(1.2f, 0.5f, 1.2f));
	house.cubes.push_back({ secondFloor });

	// Roof: shifted up a bit more, scaled to be narrower, maybe 1.3 tall?
	Math::Mat4 roof = Math::Transform::Identity();
	roof = Math::Transform::Translate(roof,
		Math::Vec3(housePos.x, housePos.y + 1.5f, housePos.z));
	roof = Math::Transform::Scale(roof, Math::Vec3(1.2f, 0.6f, 1.2f));
	house.cubes.push_back({ roof });

	return house;
}

CityModel GenerateCity()
{
	CityModel city;

	// For example, place houses on a small grid
	// with some spacing in x and z directions
	const int numHousesX = 5;
	const int numHousesZ = 3;
	const float spacing = 5.0f;

	for (int x = 0; x < numHousesX; x++)
	{
		for (int z = 0; z < numHousesZ; z++)
		{
			float posX = x * spacing;
			float posZ = z * spacing;
			// If you want some random offset, you could add random noise

			House h = MakeSimpleHouse(Math::Vec3(posX, 0.0f, posZ));
			city.houses.push_back(h);
		}
	}

	return city;
}

void DrawCity(const CityModel& city,
	const Math::Mat4& viewMatrix,
	float aspectRatio,
	Render::Shader& shader,
	Render::VertexArray& _vaoCube)
{
	// Make a projection matrix
	Math::Mat4 projectionMatrix = Math::Perspective(Math::Radians(45.0f), aspectRatio, 0.1f, 100.0f);

	// For each house in the city
	for (const House& house : city.houses)
	{
		// For each cube that makes up this house
		for (const CubeInstance& inst : house.cubes)
		{
			// Build final transform = projection * view * model
			Math::Mat4 transform = projectionMatrix * viewMatrix;
			transform = transform * inst.modelMatrix;

			// Set the uniform
			shader.SetUniform("transform", transform);

			// Draw the cube
			Render::DrawIndexed(_vaoCube);
		}
	}
}

SimpleScene::SimpleScene()
	: Core::Layer("SimpleScene")
{
}

void SimpleScene::OnAttach()
{
#ifndef PLATFORM_ANDROID
	Input::SetCursorVisible(false);
#endif
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
	_shader.BindTexture2D(1, _textureWall);

	const auto [windowWidth, windowHeight] = Core::Application::GetWindowSize();
	const float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
	const auto time = Core::GetTimeManager().GetAppTime();
	// Draw quad
	{
		Math::Mat4 modelMatrix { 1.0f };
		modelMatrix = Math::Transform::Translate(modelMatrix, Math::Vec3(-0.15f, -0.5f, 0.0f));
		modelMatrix = Math::Transform::Rotate(modelMatrix, Math::Radians(-90.0f), Math::Vec3(1.0f, 0.0f, 0.0f));
		modelMatrix = Math::Transform::Scale(modelMatrix, { 4.0f, 4.0f, 1.0f });

		Math::Mat4 viewMatrix = _camera.GetViewMatrix();

		Math::Mat4 projectionMatrix { 1.0f };
		projectionMatrix = Math::Perspective(Math::Radians(45.0f), aspectRatio, 0.1f, 100.0f);

		Math::Mat4 transform = projectionMatrix * viewMatrix * modelMatrix;
		_shader.SetUniform("transform", transform);
	}
	Render::DrawIndexed(_vao);

	DrawCity(gCityModel, _camera.GetViewMatrix(), aspectRatio, _shader, _vaoCube);

	_shader.Unbind();
}

void SimpleScene::OnImGuiRender()
{
}

void SimpleScene::OnEvent(Core::Event& event)
{
	Core::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Core::KeyPressedEvent>([this](Core::KeyPressedEvent& e) {
		if (e.GetKeyCode() == Keycode::KEY_1) {
			_isCameraInputEnabled = !_isCameraInputEnabled;
			Input::SetCursorVisible(!Input::IsCursorVisible());
		}
		return false;
	});

	if (_isCameraInputEnabled) {
		dispatcher.Dispatch<Core::MouseMovedEvent>([this](Core::MouseMovedEvent& event) {
			_camera.OnMouseMovedEvent(event.GetX(), event.GetY());
			return false;
		});
	}
}

void SimpleScene::SetupScene()
{
	_shader = Core::GetAssetManager().LoadShader("textured_transform");
	_texture0 = Core::GetAssetManager().LoadTexture("awesomeface");
	_textureWall = Core::GetAssetManager().LoadTexture("wall");

	gCityModel = GenerateCity();

	// quad
	Render::VertexBuffer vb({
		// positions		  // colors		   // texture coords
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 8.0f, 8.0f,   // top right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 8.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 8.0f,  // top left
	});

	Render::IndexBuffer eb({
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	});

	Render::BufferLayout layout({ { "position", Render::RenderType::Float3 },
		{ "color", Render::RenderType::Float3 },
		{ "texCoord", Render::RenderType::Float2 } });

	vb.SetLayout(layout);
	_vao.AddVertexBuffer(std::move(vb));
	_vao.SetIndexBuffer(std::move(eb));

	// cube
	// positions        // colors         // texture coords
	Render::VertexBuffer vbCube({
		// ---- Face 0: Front (z = +0.5), color = red (1,0,0) ----
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // [0]  top right
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // [1]  bottom right
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // [2]  bottom left
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // [3]  top left

		// ---- Face 1: Back (z = -0.5), color = green (0,1,0) ----
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,   // [4]  top right
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // [5]  bottom right
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // [6]  bottom left
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // [7]  top left

		// ---- Face 2: Left (x = -0.5), color = blue (0,0,1) ----
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // [8]  top right
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // [9]  bottom right
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // [10] bottom left
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // [11] top left

		// ---- Face 3: Right (x = +0.5), color = yellow (1,1,0) ----
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // [12] top right
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // [13] bottom right
		0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,  // [14] bottom left
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // [15] top left

		// ---- Face 4: Top (y = +0.5), color = cyan (0,1,1) ----
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,   // [16] top right
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // [17] bottom right
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // [18] bottom left
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  // [19] top left

		// ---- Face 5: Bottom (y = -0.5), color = magenta (1,0,1) ----
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,   // [20] top right
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // [21] bottom right
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // [22] bottom left
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // [23] top left
	});

	Render::IndexBuffer ebCube({ // Face 0 (indices [0..3])
		0, 1, 3,
		1, 2, 3,

		// Face 1 (indices [4..7])
		4, 5, 7,
		5, 6, 7,

		// Face 2 (indices [8..11])
		8, 9, 11,
		9, 10, 11,

		// Face 3 (indices [12..15])
		12, 13, 15,
		13, 14, 15,

		// Face 4 (indices [16..19])
		16, 17, 19,
		17, 18, 19,

		// Face 5 (indices [20..23])
		20, 21, 23,
		21, 22, 23 });

	vbCube.SetLayout(layout);
	_vaoCube.AddVertexBuffer(std::move(vbCube));
	_vaoCube.SetIndexBuffer(std::move(ebCube));

	// _camera.SetPosition({ 0.0f, 0.0f, 3.0f });
	_camera.SetPosition({ -7.8026237f, 4.8330536f, -3.892373f });
	_camera.SetYaw(37.399975f);
	_camera.SetPitch(-18.199987f);
}
