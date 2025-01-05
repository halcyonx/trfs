#include "File.h"
#include <IO/FileReader.h>
#include <filesystem>

static std::string assetRoot = "";

static std::string GetBasePath()
{
#if PLATFORM_ANDROID
	return {};
#endif

	if (!assetRoot.empty()) {
		return assetRoot;
	}

	std::string basePath = "assets";

	for (int i = 0; i < 5; i++) {
		if (std::filesystem::exists(basePath)) {
			break;
		}
		else {
			basePath = std::string("../") += basePath;
		}
	}

	assetRoot = basePath;
	return assetRoot;
}

std::string Utils::GetAssetsRoot()
{
	static std::string basePath = GetBasePath();
	return basePath;
}

std::string Utils::GetAssetPath(const std::string& assetName)
{
	static std::string basePath = GetBasePath();
	return !basePath.empty() ? basePath + "/" + assetName : assetName;
}

std::string Utils::GetFileContent(const std::string& path)
{
	IO::FileReader reader(GetAssetPath(path));
	return reader.ReadAll();
}