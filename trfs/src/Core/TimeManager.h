#pragma once

namespace Core
{
	class TimeManager
	{
	public:
		void Update(float dt);

		float GetDt() const { return _deltaTime; }
		float GetAppTime() const { return _appTime; }
		int GetFps() const { return _fps; }
		int GetFrameNumber() const { return _frameNumber; }

	private:
		float _deltaTime = 0.0f;
		float _appTime = 0.0f;
		int _fps = 0;
		int _frameNumber = 0;
	};
} // namespace Core
