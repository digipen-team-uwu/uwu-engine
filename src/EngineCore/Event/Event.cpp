#include <UWUEngine/Event/Event.h>

template<>
int RegisterSystemHelper<EventSystem>::RegisterSystemHelper_ID = SystemUpdater::AddSystem<EventSystem>(SystemInitOrder::Event, SystemUpdateOrder::Event);

std::priority_queue<Event> EventSystem::eventQueue;

void EventSystem::Update()
{
  DispatchEvents();
}

void EventSystem::Push(const Event& event)
{
  eventQueue.push(event);
}

void EventSystem::DispatchEvents()
{
  
}
