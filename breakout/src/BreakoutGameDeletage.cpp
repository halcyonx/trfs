#include "BreakoutGameDeletage.h"
#include <Core/Subsystems.h>
#include <Core/Log.h>

BreakoutGameDeletage::BreakoutGameDeletage(int argc, char** args)
{
}

void BreakoutGameDeletage::OnLaunch()
{
	LOG_DEBUG("Sandbox OnLaunch");
	auto shader = Core::GetAssetManager().LoadShader("standard");
}

void BreakoutGameDeletage::OnUpdate(float dt)
{
}

void BreakoutGameDeletage::OnFrameBegin()
{
}

void BreakoutGameDeletage::OnRender()
{
}

void BreakoutGameDeletage::OnFrameEnd()
{
}

void BreakoutGameDeletage::OnDestroy()
{
	LOG_DEBUG("Sandbox OnDestroy");
}
