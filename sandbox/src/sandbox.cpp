#include "SandboxDelegate.h"
#include <Core/Main.h>

int Core::Main(int argc, char* args[])
{
	return Core::StartApp(new SandboxDelegate(argc, args));
}
