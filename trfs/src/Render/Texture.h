#pragma once

namespace Render
{
	class Texture
	{
	public:
		using Handle = uint32_t;

		Texture() = default;
		virtual ~Texture();
		void Reset();

		void Bind() const;
		Handle GetHandle() const { return _texture; }
		Handle Generate(int width, int height, int nrChannels, bool srgb, const void* data = nullptr);

	private:
		Handle _texture = 0;
	};
} // namespace Render
