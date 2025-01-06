#include "ExampleLayersFactory.h"
#include <examples/Empty.h>
#include <examples/Polygon.h>
#include <Core/Log.h>

std::unique_ptr<Core::Layer> ExampleLayersFactory::CreateLayer(std::string_view layerName)
{
	if (layerName == "Empty") {
		return std::make_unique<Empty>();
	}
	else if (layerName == "Polygon") {
		return std::make_unique<Polygon>();
	}

	LOG_ERROR("Unknown layer name: {0}", layerName);

	return nullptr;
}
