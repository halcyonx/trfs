#pragma once

#include <SDL_rwops.h>

namespace IO
{
	class FileReader
	{
	public:
		FileReader(const std::string& filePath);
		~FileReader();

		bool Open();
		size_t Read(void* buffer, size_t size, size_t maxnum);
		std::string ReadAll();
		int64_t GetFileSize();
		void Close();

	private:
		std::string filePath;
		SDL_RWops* rwops = nullptr;
	};
} // namespace IO
