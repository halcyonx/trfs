#include "AssetManager.h"
#include "Log.h"
#include <IO/FileReader.h>
#include <Utils/File.h>
#include <nlohmann/json.hpp>
#include <filesystem>

struct Core::AssetManager::RegisterInfo
{
	std::string path;
};

void CofigureShaderSource(std::string& shaderSource)
{
	static const std::string_view versionHolder = "#version_placeholder";
#if PLATFORM_WINDOWS || PLATFORM_MACOS
	static const std::string_view version = "#version 330 core";
#elif PLATFORM_ANDROID
	static const std::string_view version = "#version 300 es";
#endif
	if (const auto pos = shaderSource.find(versionHolder); pos != std::string::npos) {
		shaderSource.replace(pos, versionHolder.size(), version);
	}
}

std::optional<Render::Shader> LoadShaderFromFile(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
{
	const std::string root = "shaders/";
	LOG_DEBUG("Load shader from file {} {} {}", vertexPath, fragmentPath, geometryPath);

	// read vertex shader
	std::string vertexSrc = Utils::GetFileContent(root + vertexPath);
	CofigureShaderSource(vertexSrc);

	// read fragment shader
	std::string fragmentSrc = Utils::GetFileContent(root + fragmentPath);
	CofigureShaderSource(fragmentSrc);

	const std::string geometrySrc = !geometryPath.empty() ? Utils::GetFileContent(root + geometryPath) : "";

	Render::Shader shader;
	if (shader.Compile(vertexSrc, fragmentSrc, "")) {
		return shader;
	}
	return {};
}

void Core::AssetManager::RegisterAssets()
{
	const std::string shadersPath = Utils::GetAssetPath("shaders");
	RegisterInfo info { shadersPath };
	RegisterShaders(info);

	LOG_DEBUG("Shaders registered: {}", _registeredShaders.size());
}

Render::Shader Core::AssetManager::LoadShader(const std::string& name)
{
	if (_shaders.find(name) != _shaders.end()) {
		LOG_DEBUG("Shader [{}] already loaded", name);
		return _shaders[name];
	}

	auto it = _registeredShaders.find(name);
	if (it == _registeredShaders.end()) {
		LOG_ERROR("Shader [{}] not registered", name);
		return Render::Shader {};
	}

	const auto shader = LoadShaderFromFile(it->second.vertexPath, it->second.fragmentPath, {});
	if (shader.has_value()) {
		LOG_DEBUG("Shader [{}] loaded", name);
		_shaders.insert({ name, shader.value() });
		return shader.value();
	}
	else {
		LOG_ERROR("Shader [{}] not loaded", name);
	}

	return Render::Shader {};
}

Render::Shader Core::AssetManager::GetShader(const std::string& name)
{
	return Render::Shader();
}

void Core::AssetManager::RegisterShaders(const Core::AssetManager::RegisterInfo& info)
{
	const std::string filename = info.path + "/shaders.json";
	if (!filename.empty()) {
		LOG_DEBUG("Loading shaders from shaders.json");

		IO::FileReader reader(filename);
		//				std::ifstream file(filename.path().string());
		using json = nlohmann::json;
		//				json data = json::parse(file);
		json data = json::parse(reader.ReadAll());

		for (const auto& shader : data["shaders"]) {
			std::string id = shader["id"];
			std::string vertexPath = shader["vertex"];
			std::string fragmentPath = shader["fragment"];
			_registeredShaders[id] = { vertexPath, fragmentPath };
			LOG_DEBUG("Shader [{}] registered", id);
		}
	}
}
