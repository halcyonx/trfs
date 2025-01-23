#pragma once

#define EVENT_CLASS_TYPE(type)                                   \
	static EventType GetStaticType() { return EventType::type; } \
	virtual EventType GetEventType() const override { return GetStaticType(); }

namespace Core
{
	enum class EventType
	{
		KeyPressed,
		KeyReleased,
		MousePressed,
		MouseReleased,
		MouseMoved,
		MouseScrolled
	};

	class Event
	{
	public:
		bool handled = false;
		virtual EventType GetEventType() const = 0;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: _event(event)
		{
		}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (_event.GetEventType() == T::GetStaticType()) {
				_event.handled = func(static_cast<T&>(_event));
				return true;
			}
			return false;
		}

	private:
		Event& _event;
	};
} // namespace Core
