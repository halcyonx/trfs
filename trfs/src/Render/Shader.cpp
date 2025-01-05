#include "Shader.h"
#include "OpenGLConfig.h"
#include <Core/Log.h>
#include <Debug/OpenGLDebug.h>
#include <glm/gtc/type_ptr.hpp>

GLuint CreateShader(GLenum shaderType, const char* src)
{
	GLuint shader = glCreateShader(shaderType);
	if (!shader) {
		glCheckError();
		return 0;
	}
	glShaderSource(shader, 1, &src, nullptr);

	GLint compiled = GL_FALSE;
	glCompileShader(shader);
	glCheckError();
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	glCheckError();

	if (!compiled) {
		GLint infoLogLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
		if (infoLogLen > 0) {
			GLchar* infoLog = new GLchar[infoLogLen];
			if (infoLog) {
				glGetShaderInfoLog(shader, infoLogLen, nullptr, infoLog);
				LOG_ERROR("Shader compilation error: {}", infoLog);
				LOG_DEBUG("Shader source: \n{}\n", src);
				delete[] infoLog;
			}
		}
		glDeleteShader(shader);
		glCheckError();
		return 0;
	}

	return shader;
}

void Render::Shader::Bind() const
{
	glUseProgram(_program);
	glCheckError();
}

void Render::Shader::Unbind() const
{
	glUseProgram(0);
	glCheckError();
}

void Render::Shader::SetUniform(std::string_view uniformName, int value) const
{
	GLint location = glGetUniformLocation(_program, std::string(uniformName).c_str());
	//assert(location >= 0);
	glUniform1i(location, value);
}

void Render::Shader::SetUniform(std::string_view uniformName, float value) const
{
	GLint location = glGetUniformLocation(_program, std::string(uniformName).c_str());
	// assert(location >= 0);
	glUniform1f(location, value);
	glCheckError();
}

void Render::Shader::SetUniform(std::string_view uniformName, const Math::Vec2& vector) const
{
	GLint location = glGetUniformLocation(_program, std::string(uniformName).c_str());
	// assert(location >= 0);
	glUniform2fv(location, 1, &vector[0]);
	glCheckError();
}

void Render::Shader::SetUniform(std::string_view uniformName, const Math::Vec3& vector) const
{
	GLint location = glGetUniformLocation(_program, std::string(uniformName).c_str());
	// assert(location >= 0);
	glUniform3fv(location, 1, &vector[0]);
	glCheckError();
}

void Render::Shader::SetUniform(std::string_view uniformName, const Math::Vec4& vector) const
{
	GLint location = glGetUniformLocation(_program, std::string(uniformName).c_str());
	// assert(location >= 0);
	glUniform4fv(location, 1, &vector[0]);
	glCheckError();
}

void Render::Shader::SetUniform(std::string_view uniformName, const Math::Mat4& matrix) const
{
	GLint location = glGetUniformLocation(_program, std::string(uniformName).c_str());
	// assert(location >= 0);
	// glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	glCheckError();
}

void Render::Shader::SetSampler(std::string_view samplerName, int sampler) const
{
	glUniform1i(glGetUniformLocation(_program, std::string(samplerName).c_str()), sampler);
	glCheckError();
}

//	void Shader::BindTexture2D(GLuint channel, GLuint texture)
//	{
//		assert(channel < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
//		glActiveTexture(GL_TEXTURE0 + channel);
//		glCheckError();
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glCheckError();
//		SetSampler(std::string("texture_") + std::to_string(channel), channel);
//	}
//
//	void Shader::UnbindTexture2D()
//	{
//		glBindTexture(GL_TEXTURE_2D, 0);
//		glCheckError();
//	}
//
//	void Shader::BindTexture3D(GLuint channel, GLuint texture)
//	{
//		glActiveTexture(GL_TEXTURE0 + channel);
//		glCheckError();
//		glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
//		glCheckError();
//		SetSampler(std::string("texture_") + std::to_string(channel), channel);
//	}
//
//	void Shader::UnbindTexture3D()
//	{
//		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
//		glCheckError();
//	}

Render::Shader::~Shader()
{
}

GLuint Render::Shader::Compile(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource)
{
	GLuint vtxShader = 0;
	GLuint geomShader = 0;
	GLuint fragShader = 0;
	GLuint program = 0;
	GLint linked = GL_FALSE;

	vtxShader = CreateShader(GL_VERTEX_SHADER, vertexSource.c_str());
	if (!vtxShader) {
		LOG_ERROR("Vertex shader compilation failed");
		goto exit;
	}

#if PLATFORM_MACOS || PLATFORM_WINDOWS
	if (!geometrySource.empty()) {
		geomShader = CreateShader(GL_GEOMETRY_SHADER, geometrySource.c_str());
		if (!geomShader) {
			LOG_ERROR("Geometry shader compilation failed");
			goto exit;
		}
	}
#endif

	fragShader = CreateShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());
	if (!fragShader) {
		LOG_ERROR("Fragment shader compilation failed");
		goto exit;
	}

	program = glCreateProgram();
	if (!program) {
		glCheckError();
		LOG_ERROR("Shader create program failed");
		goto exit;
	}

	glAttachShader(program, vtxShader);
	glCheckError();

	if (!geometrySource.empty()) {
		glAttachShader(program, geomShader);
		glCheckError();
	}

	glAttachShader(program, fragShader);
	glCheckError();

	glLinkProgram(program);
	glCheckError();
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	glCheckError();

	if (!linked) {
		LOG_ERROR("Shader link program failed");
		GLint infoLogLen = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);

		if (infoLogLen) {
			GLchar* infoLog = new GLchar[infoLogLen];

			if (infoLog) {
				glGetProgramInfoLog(program, infoLogLen, nullptr, infoLog);
				LOG_ERROR("Info: {}", infoLog);
				delete[] infoLog;
			}
		}

		glDeleteProgram(program);
		glCheckError();
		program = 0;
	}

exit:
	glDeleteShader(vtxShader);
	glCheckError();
	glDeleteShader(fragShader);
	glCheckError();
	_program = program;
	return _program;
}

void Render::Shader::Reset()
{
	if (_program) {
		glDeleteProgram(_program);
		glCheckError();
		_program = 0;
	}
}
