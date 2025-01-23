#include "Input.h"
#include <Core/Log.h>
#include <SDL2/SDL.h>

constexpr int keyMapping[] = {
	SDLK_a,
	SDLK_b,
	SDLK_c,
	SDLK_d,
	SDLK_e,
	SDLK_f,
	SDLK_g,
	SDLK_h,
	SDLK_i,
	SDLK_j,
	SDLK_k,
	SDLK_l,
	SDLK_m,
	SDLK_n,
	SDLK_o,
	SDLK_p,
	SDLK_q,
	SDLK_r,
	SDLK_s,
	SDLK_t,
	SDLK_u,
	SDLK_v,
	SDLK_w,
	SDLK_x,
	SDLK_y,
	SDLK_z,
	SDLK_0,
	SDLK_1,
	SDLK_2,
	SDLK_3,
	SDLK_4,
	SDLK_5,
	SDLK_6,
	SDLK_7,
	SDLK_8,
	SDLK_9,
	SDLK_F1,
	SDLK_F2,
	SDLK_F3,
	SDLK_F4,
	SDLK_F5,
	SDLK_F6,
	SDLK_F7,
	SDLK_F8,
	SDLK_F9,
	SDLK_F10,
	SDLK_F11,
	SDLK_F12,
	SDLK_UP,
	SDLK_DOWN,
	SDLK_LEFT,
	SDLK_RIGHT,
	SDLK_SPACE,
	SDLK_RETURN,
	SDLK_ESCAPE,
	SDLK_BACKSPACE,
	SDLK_TAB,
	SDLK_LSHIFT,
	SDLK_RSHIFT,
	SDLK_LCTRL,
	SDLK_RCTRL,
	SDLK_LALT,
	SDLK_RALT,
	SDLK_CAPSLOCK,
	SDLK_INSERT,
	SDLK_DELETE,
	SDLK_HOME,
	SDLK_END,
	SDLK_PAGEUP,
	SDLK_PAGEDOWN,
	SDLK_COMMA,
	SDLK_PERIOD,
	SDLK_SLASH,
	SDLK_SEMICOLON,
	SDLK_QUOTE,
	SDLK_LEFTBRACKET,
	SDLK_RIGHTBRACKET,
	SDLK_BACKSLASH,
	SDLK_MINUS,
	SDLK_EQUALS,
	SDLK_NUMLOCKCLEAR,
	SDLK_PRINTSCREEN,
	SDLK_SCROLLLOCK,
	SDLK_PAUSE
};

bool Input::IsKeyPressed(Keycode keycode)
{
	const Uint8* state = SDL_GetKeyboardState(nullptr);
	const int code = keyMapping[static_cast<int>(keycode)];
	return state[SDL_GetScancodeFromKey(code)] == 1; // 1 indicates the key is pressed
}

bool Input::SetCursorVisible(bool visible)
{
	if (visible) {
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_ShowCursor(SDL_ENABLE);
		return true;
	}
	else {
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_ShowCursor(SDL_DISABLE);
		return false;
	}
}

bool Input::IsCursorVisible()
{
	return SDL_GetRelativeMouseMode() == SDL_FALSE;
}

Keycode Input::CastIntToKeycode(int code)
{
	constexpr int keyMapSize = sizeof(keyMapping) / sizeof(keyMapping[0]);
	for (int i = 0; i < keyMapSize; i++) {
		if (keyMapping[i] == code) {
			return static_cast<Keycode>(i);
		}
	}
	LOG_ERROR("Wrong key code mapping");
	return Keycode::KEY_0;
}
