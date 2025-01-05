#pragma once

#include <Render/Shader.h>

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

	public:
		struct ShaderInfo
		{
			std::string vertexPath;
			std::string fragmentPath;
		};

	private:
		struct RegisterInfo;
		void RegisterShaders(const RegisterInfo& info);

	private:
		std::unordered_map<std::string, ShaderInfo> _registeredShaders;
		std::unordered_map<std::string, Render::Shader> _shaders;
	};
} // namespace Core
