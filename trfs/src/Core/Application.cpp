#include "Application.h"
#include "Layer.h"
#include "Log.h"
#include "GameDelegate.h"
#include "Subsystems.h"
#include "ImguiLayer.h"
#include <Version.h>
#include <SDL.h>

#if PLATFORM_WINDOWS || PLATFORM_MACOS
#include <glad/glad.h>
#elif PLATFORM_ANDROID
#if __ANDROID_API__ >= 23
#include <GLES3/gl32.h>
#elif __ANDROID_API__ >= 21
#include <GLES3/gl31.h>
#else
#include <GLES3/gl3.h>
#endif
#endif

namespace Core
{
	static SDL_Window* window = nullptr;
	static SDL_GLContext context = nullptr;
	static Application* _appInstance = nullptr;

	Application& Application::GetInstance()
	{
		return *_appInstance;
	}

	std::unique_ptr<Subsystems> CreateSubsystems()
	{
		return std::make_unique<Subsystems>();
	}

	std::pair<int, int> Application::GetWindowSize()
	{
		return { 1024, 768 };
	}

	Application::Application()
	{
		_appInstance = this;
		InitializeLogger();

		LOG_DEBUG("trfs version: {}", TRFS_VERSION);

		SDL_Init(SDL_INIT_VIDEO);
#if PLATFORM_MACOS
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#if PLATFORM_ANDROID
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#else
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

		// Create window with graphics context
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		//Get device display mode
		const auto [width, height] = GetWindowSize();
		SDL_Rect screenRect = { 0, 0, width, height };
#if PLATFORM_ANDROID
		SDL_DisplayMode displayMode;
		if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0) {
			screenRect.w = displayMode.w;
			screenRect.h = displayMode.h;
		}
		const Uint32 windowFlags = SDL_WINDOW_OPENGL;
#else
		const Uint32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
#endif

		window = SDL_CreateWindow("SDL OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenRect.w, screenRect.h, windowFlags);
		context = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, context);
		SDL_GL_SetSwapInterval(1); // Enable vsync

#if PLATFORM_WINDOWS || PLATFORM_MACOS
		gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
//	if (!gladLoadGL()) {
//		success = false;
//		return false;
//	}
#endif

		LOG_DEBUG("OpenGL loaded");
		LOG_DEBUG("Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		LOG_DEBUG("Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		LOG_DEBUG("Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		LOG_DEBUG("SDL version: {}.{}.{}", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);
	}

	Application::~Application()
	{
	}

	void Application::Run(GameDelegate* gameDelegate)
	{
		auto subsystems = CreateSubsystems();
		GetAssetManager().RegisterAssets();

		_gameDelegate = gameDelegate;
		bool running = true;
		SDL_Event event;

		_gameDelegate->OnLaunch();

		const auto imguiLayer = ImguiLayer(window, context);

		float deltaTime = 0.0f;
		auto prevTime = SDL_GetTicks();
		auto& timeManager = SubsystemsHolder::Get().GetTimeManager();

		while (running) {
			auto currentTime = SDL_GetTicks();
			deltaTime = static_cast<float>(currentTime - prevTime) / 1000.0f;
			prevTime = currentTime;
			timeManager.Update(deltaTime);

			while (SDL_PollEvent(&event) != 0) {
				imguiLayer.OnEvent(event);

				if (event.type == SDL_QUIT) {
					running = false;
				}
				else if (event.type == SDL_WINDOWEVENT
						 && event.window.event == SDL_WINDOWEVENT_CLOSE
						 && event.window.windowID == SDL_GetWindowID(window)) {
					running = false;
				}

				if (event.type == SDL_KEYDOWN) {
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						running = false;
						break;
					}
				}
			}

			PrepareLayers();

			// imgui routine
			imguiLayer.OnNewFrame();
			for (auto layer : _layerStack) {
				layer->OnImGuiRender();
			}
			imguiLayer.Render();

			_gameDelegate->OnFrameBegin();
			_gameDelegate->OnUpdate(deltaTime);
			_gameDelegate->OnRender();

			ProcessLayers(deltaTime);

			imguiLayer.OnEndFrame();
			_gameDelegate->OnFrameEnd();

			SDL_GL_SwapWindow(window);
		}

		imguiLayer.Shutdown();
		_gameDelegate->OnDestroy();

		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
		SDL_Quit();

		LOG_DEBUG("Application stopped");
	}

	void Application::Stop()
	{
		_running = false;
	}

	void Application::PushLayer(Layer* layer)
	{
		_newLayers.push_back(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		_layerStack.PushOverlay(overlay);
	}

	void Application::PopLayer(Layer* layer)
	{
		_oldLayers.push_back(layer);
	}

	void Application::PrepareLayers()
	{
		if (!_oldLayers.empty()) {
			for (auto layer : _oldLayers) {
				_layerStack.PopLayer(layer);
			}
			_oldLayers.clear();
		}

		if (!_newLayers.empty()) {
			for (auto layer : _newLayers) {
				_layerStack.PushLayer(layer);
			}
			_newLayers.clear();
		}
	}

	void Application::ProcessLayers(float deltaTime)
	{
		for (auto layer : _layerStack) {
			layer->OnUpdate(deltaTime);
		}

		for (auto layer : _layerStack) {
			layer->OnRender();
		}
	}
} // namespace Core
