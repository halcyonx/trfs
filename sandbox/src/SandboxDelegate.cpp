#include "SandboxDelegate.h"
#include "GameLayer.h"
#include <Core/Application.h>
#include <Core/Subsystems.h>
#include <Core/Log.h>
#include <Render/RenderFunc.h>
#include "ExampleLayersFactory.h"

SandboxDelegate::SandboxDelegate(int argc, char** args)
	: _gameLayer(std::make_unique<GameLayer>(std::bind(&SandboxDelegate::SetExampleLayer, this, std::placeholders::_1)))
	, _exampleLayer(ExampleLayersFactory::CreateLayer("Empty"))
{
}

SandboxDelegate::~SandboxDelegate() = default;

void SandboxDelegate::OnLaunch()
{
	LOG_DEBUG("Sandbox OnLaunch");
	auto shader = Core::GetAssetManager().LoadShader("standard");
	Core::Application::GetInstance().PushLayer(_gameLayer.get());
	Core::Application::GetInstance().PushLayer(_exampleLayer.get());
}

void SandboxDelegate::OnUpdate(float /*dt*/)
{
}

void SandboxDelegate::OnFrameBegin()
{
	if (_newLayer) {
		_exampleLayer = std::move(_newLayer);
		_newLayer = nullptr;
	}
}

void SandboxDelegate::OnRender()
{
	Render::ClearColor(0.0, 0.0, 0.0, 1.0);
	Render::Clear();
}

void SandboxDelegate::OnFrameEnd()
{
	if (!_newLayerName.empty()) {
		if (_exampleLayer->GetName() == _newLayerName) {
			return;
		}

		auto& application = Core::Application::GetInstance();
		application.PopLayer(_exampleLayer.get());
		_newLayer = ExampleLayersFactory::CreateLayer(_newLayerName);
		application.PushLayer(_newLayer.get());
		_newLayerName.clear();
	}
}

void SandboxDelegate::OnDestroy()
{
	Core::Application::GetInstance().PopLayer(_gameLayer.get());
	LOG_DEBUG("Sandbox OnDestroy");
}

void SandboxDelegate::SetExampleLayer(std::string_view layerName)
{
	_newLayerName = layerName;
}
