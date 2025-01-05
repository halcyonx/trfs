#pragma once

namespace Core
{
	class Layer;

	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack() = default;

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		Layer* GetFirst() const { return _layers.front(); }
		Layer* GetLast() const { return _layers.back(); }
		std::vector<Layer*> GetLayers() const { return _layers; }

		std::vector<Layer*>::iterator begin() { return _layers.begin(); }
		std::vector<Layer*>::iterator end() { return _layers.end(); }

	private:
		std::vector<Layer*> _layers;
		uint32_t _layerInsertIndex = 0;
	};
} // namespace Core
