#pragma once

#include <Core/GameDelegate.h>

class BreakoutGameDeletage : public Core::GameDelegate
{
public:
	BreakoutGameDeletage(int argc, char* args[]);
	~BreakoutGameDeletage() = default;

	void OnLaunch() override;
	void OnUpdate(float dt) override;
	void OnFrameBegin() override;
	void OnRender() override;
	void OnFrameEnd() override;
	void OnDestroy() override;
};
