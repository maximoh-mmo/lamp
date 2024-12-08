#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include "Lamp_Interface.h"
#include "utils.h"

namespace Lamp
{
	using EventID = uint32_t;

	namespace LampEventID
	{
		enum Enum : EventID
		{
			FIRST,
			INVALID = FIRST,
			WindowSizeChanged,
			COUNT
		};
	}

	class IEvent
	{
	public:
		IEvent() = default;
		virtual ~IEvent() = default;
		virtual EventID GetID() const = 0;

	private:
		IEvent(const IEvent&& other) = delete;
		IEvent& operator=(const IEvent&& other) = delete;
	};

	using OnEventCB = std::function<void(const std::shared_ptr<IEvent>& event)>;

	class EventBus
	{
	public:
		LAMP_API static EventBus* GetInstance();

		LAMP_API EventBus() = default;
		LAMP_API ~EventBus() = default;

		LAMP_API void Event(const std::shared_ptr<IEvent>& event);
		LAMP_API void Register(EventID id, size_t callerUID, const OnEventCB& cb);
		LAMP_API void UnRegister(EventID id, size_t callerUID);

	private:
		DISALLOW_MOVE_COPY(EventBus)

		struct EventHandler
		{
			size_t m_unique_event_id;
			OnEventCB m_callback;
		};

		std::unordered_map<EventID, std::vector<EventHandler>> m_event_handlers;
	};
}
