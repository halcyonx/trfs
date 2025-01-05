#pragma once

#include "AssetManager.h"

namespace Core
{
	class AssetManager;
	class Subsystems;

	class SubsystemsHolder
	{
	public:
		SubsystemsHolder(Subsystems* subsystems);

		static void Set(Subsystems* subsystems) { _subsystems = subsystems; }
		static Subsystems& Get() { return *_subsystems; }

	private:
		static Subsystems* _subsystems;
	};

	class Subsystems
	{
	public:
		Subsystems()
		{
			SubsystemsHolder(this);
		}

		AssetManager& GetAssetManager() { return _assetManager; }

	private:
		AssetManager _assetManager;
	};

	AssetManager& GetAssetManager();
} // namespace Core
