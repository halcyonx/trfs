#pragma once

//#include <Math/MathTypes.h>

namespace Render
{
	class Shader
	{
	public:
		Shader() = default;
		~Shader();

		void Reset();
		void Bind() const;
		void Unbind() const;

		void SetUniform(std::string_view uniformName, int value) const;
		void SetUniform(std::string_view uniformName, float value) const;
		void SetUniform(std::string_view uniformName, const Math::Vec2& vector) const;
		void SetUniform(std::string_view uniformName, const Math::Vec3& vector) const;
		void SetUniform(std::string_view uniformName, const Math::Vec4& vector) const;
		void SetUniform(std::string_view uniformName, const Math::Mat4& matrix) const;
		void SetSampler(std::string_view samplerName, int sampler) const;

		//		void BindTexture2D(GLuint channel, GLuint texture);
		//		void BindTexture3D(GLuint channel, GLuint texture);
		//		void UnbindTexture2D();
		//		void UnbindTexture3D();

		unsigned int GetProgram() const { return _program; }
		unsigned int Compile(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource);

	private:
		unsigned int _program = 0;
	};

} // namespace Render
