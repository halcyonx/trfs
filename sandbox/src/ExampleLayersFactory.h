#pragma once

namespace Core
{
	class Layer;
} // namespace Core

class ExampleLayersFactory
{
public:
	static void RegisterLayers();
	static std::unique_ptr<Core::Layer> CreateLayer(std::string_view layerName);
	static std::vector<std::string> GetLayerNames();
};
