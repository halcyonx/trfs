#include <Core/Main.h>
#include <gtest/gtest.h>

int Core::Main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}