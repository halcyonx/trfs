#pragma once

#include <Core/Layer.h>

class Triangle : public Core::Layer
{
public:
	Triangle();
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnRender() override;
	void OnImGuiRender() override;

private:
};
