#include "RenderFunc.h"
#include "Types.h"
#include "OpenGLConfig.h"
#include <Core/Log.h>

namespace
{
	GLuint VBO, VAO, EBO;
	// Vertex data for a 2D quad (two triangles)
	// Each vertex has position (x, y) and color (r, g, b)
	GLfloat vertices[] = {
		// Positions    // Colors
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Bottom Right
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   // Top Right
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f   // Top Left
	};

	GLuint indices[] = {
		// Note that we start from 0!
		0, 1, 2, // First Triangle
		0, 2, 3  // Second Triangle
	};
} // namespace

static void InitQuad()
{
	static bool initialized = false;
	if (initialized) {
		return;
	}
	initialized = true;

	// Generate and bind the Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generate and bind the Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Generate and bind the Element Buffer Object
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Unbind the VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	glBindVertexArray(0);
}

static GLenum PrimitiveTypeToDrawMode(Render::PrimitiveType primitiveType)
{
	switch (primitiveType)
	{
		case Render::PrimitiveType::Points:
			return GL_POINTS;
		case Render::PrimitiveType::Lines:
			return GL_LINES;
		case Render::PrimitiveType::LineStrip:
			return GL_LINE_STRIP;
		case Render::PrimitiveType::LineLoop:
			return GL_LINE_LOOP;
		case Render::PrimitiveType::Triangles:
			return GL_TRIANGLES;
		case Render::PrimitiveType::TriangleStrip:
			return GL_TRIANGLE_STRIP;
		case Render::PrimitiveType::TriangleFan:
			return GL_TRIANGLE_FAN;
		default:
			LOG_ERROR("Unknown primitive type");
			return GL_TRIANGLES;
	}
}

void Render::DrawQuad()
{
	InitQuad();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

static void DrawIndexedImpl(Render::PrimitiveType primitiveType, int count, int offset, uint16_t* indices)
{
	glDrawElements(PrimitiveTypeToDrawMode(primitiveType), count, GL_UNSIGNED_INT, indices + offset);
	glBindVertexArray(0);
}

void Render::DrawIndexed(const VertexArray& vertexArray, Render::PrimitiveType primitiveType)
{
	vertexArray.Bind();
	DrawIndexedImpl(primitiveType, vertexArray.GetIndexBuffer().Count(), 0, nullptr);
}

void Render::DrawPrimitives(const VertexArray& vertexArray, Render::PrimitiveType primitiveType, int count)
{
	vertexArray.Bind();
	glDrawArrays(PrimitiveTypeToDrawMode(primitiveType), 0, count);
	glBindVertexArray(0);
}

void Render::ClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void Render::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::EnableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void Render::DisableDepthTest()
{
	glDisable(GL_DEPTH_TEST);
}
