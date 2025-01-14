#pragma once

#include <glm/glm.hpp>

namespace Render
{
	using Color = glm::vec3;
	using Color4 = glm::vec4;
	using Position = glm::vec3;
	using Position2D = glm::vec2;
	using Size2D = glm::vec2;
	using Velocity2D = glm::vec2;
	using TexCoords = glm::vec2;
	using Vec3 = glm::vec3;
	using Mat4 = glm::mat4;

	enum class PrimitiveType
	{
		Points,
		Lines,
		LineStrip,
		LineLoop,
		Triangles,
		TriangleStrip,
		TriangleFan
	};

	enum class RenderType
	{
		Bool,
		Int,
		Int2,
		Int3,
		Int4,
		Float,
		Float2,
		Float3,
		Float4,
		None
	};

	uint16_t RenderTypeSize(RenderType renderType);

	struct BufferElement
	{
		std::string _name;
		RenderType _renderType;
		int _size;
		int _offset;
		bool _normalized;

		BufferElement() = default;
		BufferElement(const std::string& name, RenderType renderType, bool normalized = false);
		uint32_t GetComponentsNumber() const;
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(std::initializer_list<BufferElement> elements)
			: _elements(elements)
		{
			CalculateOffsetAndStride();
		}

		BufferLayout(BufferLayout&& rhs)
			: _elements(std::move(rhs._elements))
			, _stride(rhs._stride)
		{
		}

		BufferLayout& operator=(BufferLayout&& rhs)
		{
			if (this == &rhs) {
				return *this;
			}
			_elements = std::move(rhs._elements);
			_stride = rhs._stride;
			return *this;
		}

		BufferLayout& operator=(const BufferLayout& rhs)
		{
			if (this == &rhs) {
				return *this;
			}
			_elements = rhs._elements;
			_stride = rhs._stride;
			return *this;
		}

		uint32_t GetStride() const { return _stride; }
		const std::vector<BufferElement>& GetElements() const { return _elements; }

		std::vector<BufferElement>::iterator begin() { return _elements.begin(); }
		std::vector<BufferElement>::iterator end() { return _elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return _elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return _elements.end(); }

	private:
		void CalculateOffsetAndStride()
		{
			uint32_t offset = 0;
			_stride = 0;

			for (auto& element : _elements) {
				element._offset = offset;
				offset += element._size;
				_stride += element._size;
			}
		}

	private:
		std::vector<BufferElement> _elements;
		uint32_t _stride = 0;
	};

	struct Vertex
	{
		Position position;
		Color color;

		Vertex(const Vec3& pos, const Color& col)
			: position(pos)
			, color(col)
		{
		}
	};

	class VertexBuffer
	{
	public:
		VertexBuffer() = default;
		VertexBuffer(const float* vertices, size_t size);
		VertexBuffer(std::initializer_list<float> vertices);
		VertexBuffer(const std::vector<float>& vertices);
		VertexBuffer(const std::vector<Vertex>& vertices);

		VertexBuffer(const VertexBuffer&) = delete;
		VertexBuffer& operator=(const VertexBuffer&) = delete;

		VertexBuffer(VertexBuffer&& rhs);

		~VertexBuffer();

		void Bind() const;
		void Unbind();
		void SetLayout(BufferLayout&& bufferLayout);
		void SetLayout(const BufferLayout& bufferLayout);
		const BufferLayout& GetLayout() const;

	private:
		uint32_t _vertexBuffer = 0;
		BufferLayout _bufferLayout;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer() = default;
		IndexBuffer(const int* indices, int size);
		IndexBuffer(std::initializer_list<int> vertices);
		IndexBuffer(const std::vector<int>& vertices);
		~IndexBuffer();

		IndexBuffer(IndexBuffer&& rhs);
		IndexBuffer& operator=(IndexBuffer&& rhs);

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

		void Bind() const;
		void Unbind();
		int Count() const;

	private:
		uint32_t _indexBuffer = 0;
		uint32_t _size = 0;
	};

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void SetIndexBuffer(IndexBuffer&& indexBuffer);
		void AddVertexBuffer(VertexBuffer&& vertexBuffer);
		const IndexBuffer& GetIndexBuffer() const;

	private:
		uint32_t _vertexArray = 0;
		IndexBuffer _indexBuffer;
		std::vector<VertexBuffer> _vertexBuffers;
	};
} // namespace Render
