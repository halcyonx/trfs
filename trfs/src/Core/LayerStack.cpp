#include "LayerStack.h"
#include "Layer.h"
#include "Log.h"

namespace Core
{
	void LayerStack::PushLayer(Layer* layer)
	{
		_layers.emplace(_layers.begin() + _layerInsertIndex, layer);
		_layerInsertIndex++;
		layer->OnAttach();
		LOG_DEBUG("[{}] attached", layer->GetName());
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		_layers.emplace_back(overlay);
		overlay->OnAttach();
		LOG_DEBUG("[{}] overlay attached", overlay->GetName());
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(_layers.begin(), _layers.begin() + _layerInsertIndex, layer);
		if (it != _layers.begin() + _layerInsertIndex) {
			_layers.erase(it);
			layer->OnDetach();
			LOG_DEBUG("[{}] detached", layer->GetName());
			_layerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(_layers.begin() + _layerInsertIndex, _layers.end(), overlay);
		if (it != _layers.end()) {
			overlay->OnDetach();
			_layers.erase(it);
		}
	}
} // namespace Core
