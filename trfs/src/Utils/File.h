#pragma once

namespace Utils
{
	std::string GetAssetsRoot();
	std::string GetAssetPath(const std::string& assetName);
	std::string GetFileContent(const std::string& path);
} // namespace Utils
