#include "Subsystems.h"

Core::Subsystems* Core::SubsystemsHolder::_subsystems = nullptr;

Core::SubsystemsHolder::SubsystemsHolder(Core::Subsystems* subsystems)
{
	_subsystems = subsystems;
}

Core::AssetManager& Core::GetAssetManager()
{
	return Core::SubsystemsHolder::Get().GetAssetManager();
}

Core::TimeManager& Core::GetTimeManager()
{
	return Core::SubsystemsHolder::Get().GetTimeManager();
}
