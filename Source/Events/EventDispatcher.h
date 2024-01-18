#pragma once

#include <set>

class IEventHandler;
class Event;

// Subject
class EventDispatcher {
public:
    void Subscribe(IEventHandler* handler);
    void Unsubscribe(IEventHandler* handler);
    void Dispatch(Event& event);
private:
    std::set<IEventHandler*> handlers;
};