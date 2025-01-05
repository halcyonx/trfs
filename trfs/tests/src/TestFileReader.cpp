#include <gtest/gtest.h>
#include <IO/FileReader.h>
#include <fstream>

class FileReaderTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		// Set up code, like creating a test file
		std::ofstream out("test.txt");
		out << "Hello, world!";
		out.close();
	}

	void TearDown() override
	{
		// Clean up code
		remove("test.txt");
	}
};

TEST_F(FileReaderTest, ReadsContentCorrectly)
{
	IO::FileReader reader("test.txt");
	std::string content = reader.ReadAll();
	EXPECT_EQ(content, "Hello, world!");
}

TEST_F(FileReaderTest, CheckFileSize)
{
	IO::FileReader reader("test.txt");
	const int fileSize = reader.GetFileSize();
	EXPECT_EQ(fileSize, 13);
}

TEST_F(FileReaderTest, CheckReadPartFile)
{
	IO::FileReader reader("test.txt");
	reader.Open();
	char buffer[5];
	reader.Read(buffer, 1, 5);
	EXPECT_STREQ(buffer, "Hello");
}

TEST_F(FileReaderTest, ThrowsExceptionOnInvalidFile)
{
	IO::FileReader reader("nonexistent.txt");
	EXPECT_STREQ(reader.ReadAll().c_str(), "");
}
