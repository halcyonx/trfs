//
// Created by Roman Seleznev on 12/01/2025.
//

#include "FileBuffer.h"
#include <Core/Log.h>
#include <SDL_rwops.h>

IO::FileBuffer::FileBuffer(const std::string& path)
	: _path(path)
{
	LOG_DEBUG("[FileBuffer] Loading file: {}", _path);
	_buffer = SDL_LoadFile(_path.c_str(), &_size);
}

IO::FileBuffer::~FileBuffer()
{
	if (_buffer) {
		SDL_free(_buffer);
	}
}
