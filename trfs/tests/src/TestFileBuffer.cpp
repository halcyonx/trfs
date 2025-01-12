#include <gtest/gtest.h>
#include <IO/FileBuffer.h>
#include <fstream>

// Test fixture for FileBuffer
class FileBufferTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		std::ofstream out("test.txt");
		out << "Hello, world!";
	}

	void TearDown() override
	{
		remove("test.txt");
	}
};

// Test default constructor
TEST_F(FileBufferTest, DefaultConstructor)
{
	IO::FileBuffer buffer;
	EXPECT_EQ(buffer.GetPath(), "");
	EXPECT_EQ(buffer.GetBuffer(), nullptr);
	EXPECT_EQ(buffer.GeBuffertSize(), 0);
}

// Test parameterized constructor
TEST_F(FileBufferTest, ParameterizedConstructor)
{
	std::string testPath = "test.txt";
	IO::FileBuffer buffer(testPath);
	EXPECT_EQ(buffer.GetPath(), testPath);
	EXPECT_NE(buffer.GetBuffer(), nullptr);
	EXPECT_GT(buffer.GeBuffertSize(), 0);
}

// Test GetPath method
TEST_F(FileBufferTest, GetPath)
{
	std::string testPath = "test.txt";
	IO::FileBuffer buffer(testPath);
	EXPECT_EQ(buffer.GetPath(), testPath);
}

// Test GetBuffer method
TEST_F(FileBufferTest, GetBuffer)
{
	std::string testPath = "test.txt";
	IO::FileBuffer buffer(testPath);
	EXPECT_NE(buffer.GetBuffer(), nullptr);
}

// Test GetBufferSize method
TEST_F(FileBufferTest, GetBufferSize)
{
	std::string testPath = "test.txt";
	IO::FileBuffer buffer(testPath);
	EXPECT_GT(buffer.GeBuffertSize(), 0);
}
