#pragma once

#include <Render/Shader.h>
#include <Render/Texture.h>

namespace Core
{
	class AssetManager
	{
	public:
		AssetManager() = default;
		~AssetManager() = default;

		void RegisterAssets();

		Render::Shader LoadShader(const std::string& name);
		Render::Shader GetShader(const std::string& name);

		Render::Texture LoadTexture(const std::string& name);
		Render::Texture GetTexture(const std::string& name);

	public:
		struct ShaderInfo
		{
			std::string vertexPath;
			std::string fragmentPath;
		};

		struct TextureInfo
		{
			std::string path;
		};

	private:
		struct RegisterInfo;
		void RegisterShaders(const RegisterInfo& info);
		void RegisterTextures(const RegisterInfo& info);

	private:
		std::unordered_map<std::string, ShaderInfo> _registeredShaders;
		std::unordered_map<std::string, TextureInfo> _registredTextures;
		std::unordered_map<std::string, Render::Shader> _shaders;
		std::unordered_map<std::string, Render::Texture> _textures;
	};
} // namespace Core
