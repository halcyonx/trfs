#include "Empty.h"
#include <Render/RenderFunc.h>

Empty::Empty()
	: Core::Layer("Empty")
{
}

void Empty::OnAttach()
{
}

void Empty::OnDetach()
{
}

void Empty::OnUpdate(float dt)
{
}

void Empty::OnRender()
{
	Render::ClearColor(0.3, 0.4, 0.5, 1.0);
	Render::Clear();
}

void Empty::OnImGuiRender()
{
}
