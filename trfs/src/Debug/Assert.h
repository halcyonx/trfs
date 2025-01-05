#pragma once

#if PLATFORM_MACOS
#define Assert(x, ...)                                       \
	{                                                        \
		if (!(x)) {                                          \
			LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
			__builtin_trap();                                \
		}                                                    \
	}
#elif PLATFORM_WINDOWS
#define Assert(x, ...)                                       \
	{                                                        \
		if (!(x)) {                                          \
			LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
			__debugbreak();                                  \
		}                                                    \
	}
#elif PLATFORM_ANDROID
#define Assert(x, ...)                                       \
	{                                                        \
		if (!(x)) {                                          \
			LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
			__builtin_trap();                                \
		}                                                    \
	}
#else
static_assert(false, "Unknown platform!");
#endif
