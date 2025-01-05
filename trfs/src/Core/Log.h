#ifndef BREAKOUT_LOG_H
#define BREAKOUT_LOG_H

#pragma once

#include <SDL_log.h>
#include <spdlog/spdlog.h>

namespace Core
{
	void InitializeLogger();
} // namespace Core

#if !PLATFORM_ANDROID
#define LOG_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define LOG_FATAL(...) spdlog::critical(__VA_ARGS__)
#else
#define LOG_DEBUG(f, ...) SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s", fmt::format(f, ##__VA_ARGS__).c_str())
#define LOG_INFO(f, ...) SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", fmt::format(f, ##__VA_ARGS__).c_str())
#define LOG_WARN(f, ...) SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", fmt::format(f, ##__VA_ARGS__).c_str())
#define LOG_ERROR(f, ...) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", fmt::format(f, ##__VA_ARGS__).c_str())
#define LOG_FATAL(f, ...) SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", fmt::format(f, ##__VA_ARGS__).c_str())
#endif

#define SDL_LOG_DEBUG(...) SDL_Log(__VA_ARGS__)
#define SDL_LOG_ERROR(...) SDL_Log(__VA_ARGS__)

#endif //BREAKOUT_LOG_H
