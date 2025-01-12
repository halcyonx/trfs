#pragma once

#include <IO/FileBuffer.h>

namespace Utils
{
	std::string GetAssetsRoot();
	std::string GetAssetPath(const std::string& assetName);
	std::string GetFileContent(const std::string& path);
	IO::FileBuffer GetFileBuffer(const std::string& path);
	std::pair<unsigned char*, int> GetFileData(const std::string& path);
} // namespace Utils
