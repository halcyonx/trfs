#pragma once

namespace IO
{
	class FileBuffer
	{
	public:
		FileBuffer() = default;
		FileBuffer(const std::string& path);
		~FileBuffer();

		const std::string& GetPath() const { return _path; }
		void* GetBuffer() const { return _buffer; }
		size_t GeBuffertSize() const { return _size; }

	private:
		std::string _path;
		void* _buffer = nullptr;
		size_t _size = 0;
	};
} // namespace IO
