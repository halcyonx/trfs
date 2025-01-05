#pragma once

#include <Core/Layer.h>

class Empty : public Core::Layer
{
public:
	Empty();
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(float dt) override;
	void OnRender() override;
	void OnImGuiRender() override;
};
