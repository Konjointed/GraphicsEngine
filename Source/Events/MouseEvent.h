#pragma once

#include "Event.h"

class MouseMoveEvent : public Event {
public:
	MouseMoveEvent(int mouseX, int mouseY) : mouseX(mouseX), mouseY(mouseY) {}

	EventType Type() const override {
		return EventType::MouseMoved;
	}

	int MouseX() const {
		return mouseX;
	}

	int MouseY() const {
		return mouseY;
	}
private:
	int mouseX, mouseY;
};

class MouseButtonPressEvent : public Event {
public:
	MouseButtonPressEvent(int button) : button(button) {}

	EventType Type() const override {
		return EventType::MouseButtonPressed;
	}

	int Button() const {
		return button;
	}
private:
	int button;
};

class MouseButtonReleaseEvent : public Event {
public:
	MouseButtonReleaseEvent(int button) : button(button) {}

	EventType Type() const override {
		return EventType::MouseButtonReleased;
	}

	int Button() const {
		return button;
	}
private:
	int button;
};
