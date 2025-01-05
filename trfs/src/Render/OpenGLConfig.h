#pragma once

#if PLATFORM_WINDOWS || PLATFORM_MACOS
#include <glad/glad.h>
#elif PLATFORM_ANDROID
#if __ANDROID_API__ >= 23
#include <GLES3/gl32.h>
#elif __ANDROID_API__ >= 21
#include <GLES3/gl31.h>
#else
#include <GLES3/gl3.h>
#endif
#endif
