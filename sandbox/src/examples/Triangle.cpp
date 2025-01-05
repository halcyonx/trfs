#include "Triangle.h"
#include <Render/RenderFunc.h>

Triangle::Triangle()
	: Core::Layer("Triangle")
{
}

void Triangle::OnAttach()
{
}

void Triangle::OnDetach()
{
}

void Triangle::OnUpdate(float dt)
{
}

void Triangle::OnRender()
{
	Render::ClearColor(0.3, 0.4, 0.8, 1.0);
	Render::Clear();
}

void Triangle::OnImGuiRender()
{
}
