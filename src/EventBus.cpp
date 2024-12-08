#include "EventBus.h"
#include "utils.h"

Lamp::EventBus* Lamp::EventBus::GetInstance()
{
	static EventBus s_event_bus;
	return &s_event_bus;
}

void Lamp::EventBus::Event(const std::shared_ptr<IEvent>& event)
{
	std::vector<EventHandler>& event_handlers = m_event_handlers[event->GetID()];
	for (EventHandler&  event_handler : event_handlers)
	{
		event_handler.m_callback(event);
	}
}

LAMP_API void Lamp::EventBus::Register(EventID id, size_t callerUID, const OnEventCB& cb)
{
	std::vector<EventHandler>& event_handlers = m_event_handlers[id];
	const std::vector<EventHandler>::iterator iterator = std::find_if(event_handlers.begin(), 
		event_handlers.end(), [callerUID](EventHandler& handler)
		{
			return handler.m_unique_event_id == callerUID;
		});
	if (iterator != event_handlers.end())
	{
		LAMP_LOG_WARNING("Eventhandler already registered");
	}
	event_handlers.emplace_back(EventHandler{ callerUID, cb });
}

void Lamp::EventBus::UnRegister(EventID id, size_t callerUID)
{
	auto& event_handlers = m_event_handlers[id];
	const auto it = std::find_if(event_handlers.begin(), 
		event_handlers.end(), [callerUID](EventHandler& handler)
		{
			return handler.m_unique_event_id == callerUID;
		});
	if (it != event_handlers.end())
	{
		event_handlers.erase(it);
	}
}
