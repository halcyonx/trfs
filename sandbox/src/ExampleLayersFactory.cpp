#include "ExampleLayersFactory.h"
#include <examples/Empty.h>
#include <examples/Polygon.h>
#include <examples/TexturedPolygon.h>
#include <examples/Transform.h>
#include <examples/SimpleScene.h>
#include <Core/Log.h>

class FactoryImpl
{
public:
	using CreatorFunc = std::function<std::unique_ptr<Core::Layer>()>;

	static FactoryImpl& GetInstance()
	{
		static FactoryImpl instance;
		return instance;
	}

	void RegisterClass(const std::string& name, CreatorFunc creator)
	{
		auto it = std::find_if(_registry.begin(), _registry.end(), [name](const auto& p) {
			return p.first == name;
		});
		if (it != _registry.end()) {
			LOG_ERROR("Layer already registered: {}", name);
			return;
		}

		_registry.emplace_back(name, creator);
	}

	std::unique_ptr<Core::Layer> CreateInstance(std::string_view name) const
	{
		assert(!_registry.empty());
		auto it = std::find_if(_registry.begin(), _registry.end(), [name](const auto& p) {
			return p.first == name;
		});

		if (it != _registry.end()) {
			return it->second();
		}
		LOG_ERROR("Layer not found: {}", name);
		return std::make_unique<Empty>();
	}

	std::vector<std::string> GetRegisteredNames() const
	{
		std::vector<std::string> names;
		for (const auto& entry : _registry) {
			names.push_back(entry.first);
		}
		return names;
	}

private:
	using Registry = std::vector<std::pair<std::string, CreatorFunc>>;
	Registry _registry;
};

void ExampleLayersFactory::RegisterLayers()
{
	auto& instance = FactoryImpl::GetInstance();
	instance.RegisterClass("Empty", []() { return std::make_unique<Empty>(); });
	instance.RegisterClass("Polygon", []() { return std::make_unique<Polygon>(); });
	instance.RegisterClass("TexturedPolygon", []() { return std::make_unique<TexturedPolygon>(); });
	instance.RegisterClass("Transform", []() { return std::make_unique<Transform>(); });
	instance.RegisterClass("SimpleScene", []() { return std::make_unique<SimpleScene>(); });
}

std::unique_ptr<Core::Layer> ExampleLayersFactory::CreateLayer(std::string_view layerName)
{
	return FactoryImpl::GetInstance().CreateInstance(layerName);
}

std::vector<std::string> ExampleLayersFactory::GetLayerNames()
{
	return FactoryImpl::GetInstance().GetRegisteredNames();
}
