#include "TimeManager.h"

void Core::TimeManager::Update(float dt)
{
	_deltaTime = dt;
	_frameNumber++;
	_appTime += dt;

	static float timer = 0.0f;
	static int frames = 0;
	timer += dt;
	frames++;

	// count fps every 0.25 seconds
	if (timer >= 0.25f) {
		_fps = static_cast<int>(std::ceil(static_cast<float>(frames) / timer));
		timer = 0.0f;
		frames = 0;
	}
}
