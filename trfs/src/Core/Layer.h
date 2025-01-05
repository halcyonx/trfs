#pragma once

namespace Core
{
	class Layer
	{
	public:
		Layer(std::string_view name)
			: _name(name)
		{
		}

		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float dt) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const
		{
			return _name;
		}

	protected:
		std::string _name;
	};
} // namespace Core
