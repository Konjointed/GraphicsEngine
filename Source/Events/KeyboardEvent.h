#pragma once

#include <SDL.h>

#include "Event.h"

class KeyboardPressEvent : public Event {
public:
	KeyboardPressEvent(SDL_Keycode keycode) : keycode(keycode) {}

	EventType Type() const override {
		return EventType::KeyPressed;
	}

	SDL_Keycode Key() const {
		return keycode;
	}
private:
	SDL_Keycode keycode;
};

class KeyboardReleaseEvent : public Event {
public:
	KeyboardReleaseEvent(SDL_Keycode keycode) : keycode(keycode) {}

	EventType Type() const override {
		return EventType::KeyReleased;
	}

	SDL_Keycode Key() const {
		return keycode;
	}
private:
	SDL_Keycode keycode;
};
