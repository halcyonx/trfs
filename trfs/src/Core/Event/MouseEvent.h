#pragma once

#include "Event.h"

namespace Core
{
	class MouseMovedEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseMoved)

		MouseMovedEvent(int x, int y)
			: _mouseX(x)
			, _mouseY(y)
		{
		}

		int GetX() const { return _mouseX; }
		int GetY() const { return _mouseY; }

	private:
		int _mouseX, _mouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseScrolled)

		MouseScrolledEvent(float xOffset, float yOffset)
			: _xOffset(xOffset)
			, _yOffset(yOffset)
		{
		}

		inline float GetXOffset() const { return _xOffset; }
		inline float GetYOffset() const { return _yOffset; }

	private:
		float _xOffset, _yOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return _button; }

	protected:
		MouseButtonEvent(int button)
			: _button(button)
		{
		}

		int _button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		EVENT_CLASS_TYPE(MousePressed)

		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button)
		{
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		EVENT_CLASS_TYPE(MouseReleased)

		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button)
		{
		}
	};
} // namespace Core
