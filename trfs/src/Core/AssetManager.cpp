#include "AssetManager.h"
#include "Log.h"
#include <IO/FileReader.h>
#include <Utils/File.h>
#include <nlohmann/json.hpp>
#include <Render/OpenGLConfig.h>
#include <stb_image.h>
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

std::optional<Render::Texture> LoadTextureFromFile(const std::string& path)
{
	const std::string root = "textures/";
	LOG_DEBUG("Load texture from file {}", path);

	const GLuint wrapMode = GL_REPEAT;
	const bool srgb = false;

	const auto fileData = Utils::GetFileContent(root + path);
	auto* b = fileData.data();
	// cast const char* to const unsigned char*
	auto* buffer = reinterpret_cast<const unsigned char*>(fileData.data());
	const int fileSize = static_cast<int>(fileData.size());
	//	const unsigned char* buffer;
	//	auto* buffer = const_cast<unsigned char*>(fileData.data());

	LOG_DEBUG("Texture file path: {}, size: {}", root + path, fileSize);

	uint32_t texture = 0;
	int width, height, nrChannels;
	//	const bool flip = true;
	//	stbi_set_flip_vertically_on_load(flip);

	if (unsigned char* data = stbi_load_from_memory(buffer, fileSize, &width, &height, &nrChannels, 0)) {
		Render::Texture resultTexture;
		resultTexture.Generate(width, height, nrChannels, srgb, data);
		stbi_image_free(data);

		LOG_DEBUG("Texture loaded {}; ({}x{}:{})", path, width, height, nrChannels);

		return resultTexture;
	}
	else {
		stbi_image_free(data);
		LOG_ERROR("Texture loading failed {}", path);
	}
	//	stbi_set_flip_vertically_on_load(false);

	return {};
}

void Core::AssetManager::RegisterAssets()
{
	const std::string shadersPath = Utils::GetAssetPath("shaders");
	RegisterInfo info { shadersPath };
	RegisterShaders(info);

	const std::string texturesPath = Utils::GetAssetPath("textures");
	RegisterInfo texturesInfo { texturesPath };
	RegisterTextures(texturesInfo);

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
	if (_shaders.find(name) != _shaders.end()) {
		return _shaders[name];
	}
	return Render::Shader {};
}

Render::Texture Core::AssetManager::LoadTexture(const std::string& name)
{
	if (_textures.find(name) != _textures.end()) {
		LOG_DEBUG("Texture [{}] already loaded", name);
		return _textures[name];
	}

	auto it = _registredTextures.find(name);
	if (it == _registredTextures.end()) {
		LOG_ERROR("Texture [{}] not registered", name);
		return Render::Texture {};
	}

	const auto texture = LoadTextureFromFile(it->second.path);
	if (texture.has_value()) {
		LOG_DEBUG("Texture [{}] loaded", name);
		_textures.insert({ name, texture.value() });
		return texture.value();
	}
	else {
		LOG_ERROR("Texture [{}] not loaded", name);
	}

	return Render::Texture {};
}

void Core::AssetManager::RegisterShaders(const Core::AssetManager::RegisterInfo& info)
{
	const std::string filename = info.path + "/shaders.json";
	if (!filename.empty()) {
		LOG_DEBUG("Loading shaders from shaders.json");

		IO::FileReader reader(filename);
		using json = nlohmann::json;
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

void Core::AssetManager::RegisterTextures(const RegisterInfo& info)
{
	const std::string filename = info.path + "/textures.json";
	if (!filename.empty()) {
		LOG_DEBUG("Loading textures from textures.json");

		IO::FileReader reader(filename);
		using json = nlohmann::json;
		json data = json::parse(reader.ReadAll());

		for (const auto& texture : data["textures"]) {
			std::string id = texture["id"];
			std::string path = texture["path"];
			_registredTextures[id] = { path };
			LOG_DEBUG("Texture [{}] registered", id);
		}
	}
}
