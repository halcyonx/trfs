#include "FileReader.h"
#include <SDL_log.h>

IO::FileReader::FileReader(const std::string& filePath)
	: filePath(filePath)
{
}

IO::FileReader::~FileReader()
{
	Close();
}

bool IO::FileReader::Open()
{
	rwops = SDL_RWFromFile(filePath.c_str(), "rb");
	return rwops != nullptr;
}

size_t IO::FileReader::Read(void* buffer, size_t size, size_t maxnum)
{
	if (!rwops) {
		return 0;
	}
	return SDL_RWread(rwops, buffer, size, maxnum);
}

std::string IO::FileReader::ReadAll()
{
	if (!Open()) {
		SDL_Log("FileReader::ReadAll: failed to open file %s", filePath.c_str());
		return {};
	}

	std::string content;
	const size_t bufferSize = 1024;
	char data[bufferSize];

	while (size_t bytes = Read(data, 1, bufferSize)) {
		content.append(data, bytes);
	}

	Close();
	return content;
}

int64_t IO::FileReader::GetFileSize()
{
	if (!Open()) {
		SDL_Log("FileReader::GetFileSize: failed to open file %s", filePath.c_str());
		return 0;
	}

	int64_t size = SDL_RWsize(rwops);
	Close();
	return size;
}

void IO::FileReader::Close()
{
	if (rwops) {
		SDL_RWclose(rwops);
		rwops = nullptr;
	}
}
