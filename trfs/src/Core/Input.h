#pragma once
#include "Keycodes.h"

class Input
{
public:
	static bool IsKeyPressed(Keycode keycode);
	static bool SetCursorVisible(bool visible);
	static bool IsCursorVisible();
	static Keycode CastIntToKeycode(int code);
};
