#pragma once

#include "LayerStack.h"

namespace Core
{
	class GameDelegate;
	class Layer;
	class ImguiLayer;
	class Subsystems;

	class Application
	{
	public:
		Application();
		~Application();

		static Application& GetInstance();

		void Run(GameDelegate* gameDelegate);
		void Stop();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);

	private:
		void PrepareLayers();
		void ProcessLayers(float deltaTime);

	private:
		bool _running = true;
		float _appTime = 0.0f;
		GameDelegate* _gameDelegate = nullptr;

		LayerStack _layerStack;
		std::vector<Layer*> _oldLayers;
		std::vector<Layer*> _newLayers;
	};
} // namespace Core
