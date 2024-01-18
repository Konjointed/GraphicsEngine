#include "EventDispatcher.h"
#include "IEventHandler.h"

void EventDispatcher::Subscribe(IEventHandler* listener) {
    handlers.insert(listener);
}

void EventDispatcher::Unsubscribe(IEventHandler* listener) {
    handlers.erase(listener);
}

void EventDispatcher::Dispatch(Event& event) {
    for (auto& handler : handlers) {
        handler->OnEvent(event);
    }
}