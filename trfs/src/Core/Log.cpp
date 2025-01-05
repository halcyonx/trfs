#include "Log.h"

void Core::InitializeLogger()
{
	// Set the log priorities
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);
	SDL_LogSetPriority(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR);
	SDL_LogSetPriority(SDL_LOG_CATEGORY_SYSTEM, SDL_LOG_PRIORITY_INFO);

	spdlog::set_level(spdlog::level::trace);
	LOG_DEBUG("Logging initialized");
}
