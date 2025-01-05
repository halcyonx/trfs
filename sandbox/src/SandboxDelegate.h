#pragma once

#include <Core/GameDelegate.h>

namespace Core
{
	class Layer;
} // namespace Core

class GameLayer;

class SandboxDelegate : public Core::GameDelegate
{
public:
	SandboxDelegate(int argc, char* args[]);
	~SandboxDelegate();

	void OnLaunch() override;
	void OnUpdate(float dt) override;
	void OnFrameBegin() override;
	void OnRender() override;
	void OnFrameEnd() override;
	void OnDestroy() override;

	void SetExampleLayer(std::string_view layerName);

private:
	std::unique_ptr<GameLayer> _gameLayer;
	std::unique_ptr<Core::Layer> _exampleLayer;
	std::unique_ptr<Core::Layer> _newLayer;
	std::string _newLayerName;
};
