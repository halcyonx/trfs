#pragma once

#include "AssetManager.h"
#include "TimeManager.h"

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
		TimeManager& GetTimeManager() { return _timeManager; }

	private:
		AssetManager _assetManager;
		TimeManager _timeManager;
	};

	AssetManager& GetAssetManager();
	TimeManager& GetTimeManager();
} // namespace Core
