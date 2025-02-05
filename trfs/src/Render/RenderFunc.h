#pragma once

#include "Texture.h"

namespace Render
{
	void ClearColor(float r, float g, float b, float a);
	void Clear();

	void EnableDepthTest();
	void DisableDepthTest();

	void DrawQuad();
	void DrawIndexed(const VertexArray& vertexArray, Render::PrimitiveType primitiveType = Render::PrimitiveType::Triangles);
	void DrawPrimitives(const VertexArray& vertexArray, Render::PrimitiveType primitiveType, int count);
} // namespace Render
