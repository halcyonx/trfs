#include "Main.h"
#include "Log.h"
#include "Application.h"

#if PLATFORM_ANDROID
#include <EGL/egl.h>
#include <SDL_rwops.h>
#if __ANDROID_API__ >= 23
#include <GLES3/gl32.h>
#elif __ANDROID_API__ >= 21
#include <GLES3/gl31.h>
#else
#include <GLES3/gl3.h>
#endif
#endif

#include <SDL.h>

int main(int argc, char* args[])
{
	return Core::Main(argc, args);
}

int Core::StartApp(GameDelegate* gameDelegate)
{
	Application app;

	app.Run(gameDelegate);
	app.Stop();
	return 0;
}
