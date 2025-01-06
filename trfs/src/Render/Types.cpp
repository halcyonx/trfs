#include "Types.h"
#include "OpenGLConfig.h"
#include <Core/Log.h>
#include <cassert>

namespace Render
{
	uint16_t RenderTypeSize(RenderType renderType)
	{
		switch (renderType)
		{
			case RenderType::Int:
				return sizeof(int);
			case RenderType::Int2:
				return 2 * sizeof(int);
			case RenderType::Int3:
				return 3 * sizeof(int);
			case RenderType::Int4:
				return 4 * sizeof(int);
			case RenderType::Float:
				return sizeof(float);
			case RenderType::Float2:
				return 2 * sizeof(float);
			case RenderType::Float3:
				return 3 * sizeof(float);
			case RenderType::Float4:
				return 4 * sizeof(float);
			case RenderType::Bool:
				return sizeof(bool);

			case RenderType::None:
			default:
				LOG_ERROR("RenderTypeSize has invalid argument of renderType");
				return 0;
		}
	}

	static GLenum RenderTypeToOpengGLType(RenderType renderType)
	{
		switch (renderType)
		{
			case RenderType::Int:
			case RenderType::Int2:
			case RenderType::Int3:
			case RenderType::Int4:
				return GL_INT;
			case RenderType::Float:
			case RenderType::Float2:
			case RenderType::Float3:
			case RenderType::Float4:
				return GL_FLOAT;
			case RenderType::Bool:
				return GL_BOOL;
			case RenderType::None:
			default:
				LOG_ERROR("Unknown render type");
				return GL_FLOAT;
		}
	}

	BufferElement::BufferElement(const std::string& name, RenderType renderType, bool normalized)
		: _name(name)
		, _renderType(renderType)
		, _size(RenderTypeSize(renderType))
		, _offset(0)
		, _normalized(normalized)
	{
	}

	uint32_t BufferElement::GetComponentsNumber() const
	{
		switch (_renderType)
		{
			case RenderType::Int:
				return 1;
			case RenderType::Int2:
				return 2;
			case RenderType::Int3:
				return 3;
			case RenderType::Int4:
				return 4;
			case RenderType::Float:
				return 1;
			case RenderType::Float2:
				return 2;
			case RenderType::Float3:
				return 3;
			case RenderType::Float4:
				return 4;
			case RenderType::Bool:
				return 1;
			case RenderType::None:
			default:
				LOG_ERROR("Invalid render type in BufferElement::GetComponentsNum");
				return 0;
		}
	}

	VertexBuffer::VertexBuffer(const float* vertices, size_t size)
	{
		glGenBuffers(1, &_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::VertexBuffer(std::initializer_list<float> vertices)
		: VertexBuffer(std::data(vertices), sizeof(float) * std::size(vertices))
	{
	}

	VertexBuffer::VertexBuffer(const std::vector<float>& vertices)
		: VertexBuffer(std::data(vertices), sizeof(float) * std::size(vertices))
	{
	}

	VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices)
	{
		glGenBuffers(1, &_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * std::size(vertices), static_cast<const void*>(std::data(vertices)), GL_STATIC_DRAW);
	}

	VertexBuffer::VertexBuffer(VertexBuffer&& rhs)
		: _vertexBuffer(rhs._vertexBuffer)
		, _bufferLayout(std::move(rhs._bufferLayout))
	{
		rhs._vertexBuffer = 0;
	}

	VertexBuffer::~VertexBuffer()
	{
		if (_vertexBuffer) {
			glDeleteBuffers(1, &_vertexBuffer);
		}
	}

	void VertexBuffer::Bind() const
	{
		assert(_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	}

	void VertexBuffer::Unbind()
	{
		assert(_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexBuffer::SetLayout(BufferLayout&& bufferLayout)
	{
		_bufferLayout = std::move(bufferLayout);
	}

	void VertexBuffer::SetLayout(const BufferLayout& bufferLayout)
	{
		_bufferLayout = bufferLayout;
	}

	const BufferLayout& VertexBuffer::GetLayout() const
	{
		return _bufferLayout;
	}

	IndexBuffer::IndexBuffer(const int* indices, int size)
		: _size(size)
	{
		glGenBuffers(1, &_indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _size, indices, GL_STATIC_DRAW);
	}

	IndexBuffer::IndexBuffer(std::initializer_list<int> indices)
		: IndexBuffer(std::data(indices), static_cast<int>(sizeof(int) * std::size(indices)))
	{
	}

	IndexBuffer::IndexBuffer(const std::vector<int>& indices)
		: IndexBuffer(std::data(indices), static_cast<int>(sizeof(int) * std::size(indices)))
	{
	}

	IndexBuffer::~IndexBuffer()
	{
		if (_indexBuffer) {
			glDeleteBuffers(1, &_indexBuffer);
		}
	}

	void IndexBuffer::Bind() const
	{
		assert(_indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	}

	void IndexBuffer::Unbind()
	{
		assert(_indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	int IndexBuffer::Count() const
	{
		return _size / sizeof(int);
	}

	IndexBuffer::IndexBuffer(IndexBuffer&& rhs)
		: _indexBuffer(rhs._indexBuffer)
		, _size(rhs._size)
	{
		rhs._indexBuffer = 0;
		rhs._size = 0;
	}

	IndexBuffer& IndexBuffer::operator=(IndexBuffer&& rhs)
	{
		if (this == &rhs) {
			return *this;
		}

		_indexBuffer = rhs._indexBuffer;
		_size = rhs._size;

		rhs._indexBuffer = 0;
		rhs._size = 0;

		return *this;
	}

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &_vertexArray);
	}

	VertexArray::~VertexArray()
	{
		if (_vertexArray) {
			glDeleteVertexArrays(1, &_vertexArray);
		}
	}

	void VertexArray::Bind() const
	{
		assert(_vertexArray);
		glBindVertexArray(_vertexArray);
	}

	void VertexArray::Unbind() const
	{
		assert(_vertexArray);
		glBindVertexArray(0);
	}

	void VertexArray::SetIndexBuffer(IndexBuffer&& indexBuffer)
	{
		assert(_vertexArray);
		_indexBuffer = std::move(indexBuffer);

		glBindVertexArray(_vertexArray);
		_indexBuffer.Bind();
	}

	void VertexArray::AddVertexBuffer(VertexBuffer&& vertexBuffer)
	{
		assert(_vertexArray);
		glBindVertexArray(_vertexArray);
		vertexBuffer.Bind();

		GLuint index = 0;
		const auto& layout = vertexBuffer.GetLayout();

		for (const auto& bufferElement : layout) {
			glVertexAttribPointer(
				index,
				bufferElement.GetComponentsNumber(),
				RenderTypeToOpengGLType(bufferElement._renderType),
				bufferElement._normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				reinterpret_cast<void*>(bufferElement._offset));
			glEnableVertexAttribArray(index);
			index++;
		}

		_vertexBuffers.emplace_back(std::move(vertexBuffer));
		glBindVertexArray(0);
	}

	const IndexBuffer& VertexArray::GetIndexBuffer() const
	{
		return _indexBuffer;
	}
} // namespace Render
