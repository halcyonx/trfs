#pragma once

#include "Event.h"
#include <Core/Keycodes.h>

namespace Core
{
	// Key Events
	class KeyEvent : public Event
	{
	public:
		Keycode GetKeyCode() const { return _keycode; }

	protected:
		KeyEvent(Keycode keycode)
			: _keycode(keycode)
		{
		}

		Keycode _keycode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		EVENT_CLASS_TYPE(KeyPressed)

		KeyPressedEvent(Keycode keycode)
			: KeyEvent(keycode)
		{
		}
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		EVENT_CLASS_TYPE(KeyReleased)

		KeyReleasedEvent(Keycode keycode)
			: KeyEvent(keycode)
		{
		}
	};
} // namespace Core
