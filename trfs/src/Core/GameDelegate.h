#pragma once

namespace Core
{
	class GameDelegate
	{
	public:
		GameDelegate() = default;
		virtual ~GameDelegate() = default;

		virtual void OnLaunch() = 0;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnFrameBegin() = 0;
		virtual void OnRender() = 0;
		virtual void OnFrameEnd() = 0;
		virtual void OnDestroy() = 0;
	};
} // namespace Core
