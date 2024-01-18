#pragma once

enum class EventType {
	None = 0,
	WindowResize,
	KeyPressed,
	KeyReleased,
	MouseButtonPressed,
	MouseButtonReleased,
	MouseMoved,
	MouseScrolled
};

class Event {
public:
	virtual ~Event() = default;
	virtual EventType Type() const = 0;
};