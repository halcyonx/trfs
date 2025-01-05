#include "BreakoutGameDeletage.h"
#include <Core/Main.h>

int Core::Main(int argc, char* args[])
{
	return Core::StartApp(new BreakoutGameDeletage(argc, args));
}
