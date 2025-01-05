#include "Texture.h"
#include "OpenGLConfig.h"
#include <cassert>
#include <stb_image.h>
#include <Utils/File.h>

Render::Texture::~Texture()
{
}

void Render::Texture::Reset()
{
	glDeleteTextures(1, &_texture);
	//	glCheckError();
}

Render::Texture::Handle Render::Texture::Generate(int width, int height, int nrChannels, bool srgb, const void* data)
{
	GLint internalFormat = 0;
	GLenum dataFormat = 0;

	if (nrChannels == 1) {
		internalFormat = GL_RGB8;
		dataFormat = GL_RED;
	}
	else if (nrChannels == 3) {
		internalFormat = !srgb ? GL_RGB : GL_SRGB;
		dataFormat = GL_RGB;
	}
	else if (nrChannels == 4) {
		//internalFormat = !srgb ? GL_RGBA : GL_SRGB_ALPHA;
		dataFormat = GL_RGBA;
	}

	GLuint texture = 0;
	assert(internalFormat && dataFormat);
	glGenTextures(1, &texture);
	//	glCheckError();
	glBindTexture(GL_TEXTURE_2D, texture);
	//	glCheckError();
	// all upcoming GL_TEXTURE_2D operations now have effect on this texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//	glCheckError();
	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//	glCheckError();
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//	glCheckError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//	glCheckError();
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
	//	glCheckError();
	glGenerateMipmap(GL_TEXTURE_2D);
	//	glCheckError();
	// Unbind texture when done, so we won't accidentily mess up our texture.
	glBindTexture(GL_TEXTURE_2D, 0);
	//	glCheckError();

	_texture = texture;
	return _texture;
}

void Render::Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, _texture);
}
