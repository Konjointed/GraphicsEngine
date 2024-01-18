#pragma once

class EventDispatcher;
class Event;

// Observer
class IEventHandler {
public:
    virtual void OnEvent(Event& event) = 0;
};