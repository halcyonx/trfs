#pragma once

#include "Texture.h"

namespace Render
{
	void ClearColor(float r, float g, float b, float a);
	void Clear();
	void DrawQuad();
	void DrawIndexed(const VertexArray& vertexArray, Render::PrimitiveType primitiveType = Render::PrimitiveType::Triangles);
} // namespace Render
