#pragma once

namespace Core
{
	class Layer;
} // namespace Core

class ExampleLayersFactory
{
public:
	static std::unique_ptr<Core::Layer> CreateLayer(std::string_view layerName);
};
