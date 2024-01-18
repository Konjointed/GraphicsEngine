#include "Input.h"

#include <iostream>

#include <SDL.h>

#include "../Events/EventDispatcher.h"
#include "../Events/KeyboardEvent.h"
#include "../Events/MouseEvent.h"

Input::Input(EventDispatcher& dispatcher) : dispatcher(dispatcher)
{
	dispatcher.Subscribe(this);

    Input::MapKeyToAction(SDLK_SPACE, ActionType::Jump);
    Input::MapKeyToAction(SDLK_w, ActionType::MoveForward);
    Input::MapKeyToAction(SDLK_s, ActionType::MoveBackward);
    Input::MapKeyToAction(SDLK_a, ActionType::MoveLeft);
    Input::MapKeyToAction(SDLK_d, ActionType::MoveRight);

    Input::MapActionToKey(ActionType::Jump, SDLK_SPACE);
    Input::MapActionToKey(ActionType::MoveForward, SDLK_w);
    Input::MapActionToKey(ActionType::MoveBackward, SDLK_s);
    Input::MapActionToKey(ActionType::MoveLeft, SDLK_a);
    Input::MapActionToKey(ActionType::MoveRight, SDLK_d);
}

Input::~Input()
{
	dispatcher.Unsubscribe(this);
}

void Input::EndFrame()
{
	previousMouseX = currentMouseX;
	previousMouseY = currentMouseY;
}

bool Input::IsKeyDown(int key)
{
	auto it = keyMap.find(key);
	if (it != keyMap.end()) {
		return it->second;  // Return true if key is found and pressed, false otherwise
	}
	return false;  // Return false if key is not found in the map
}

bool Input::IsMouseButtonDown(int button)
{
	auto it = buttonMap.find(button);
	if (it != buttonMap.end()) {
		return it->second;  // Return true if button is found and pressed, false otherwise
	}
	return false;  // Return false if button is not found in the mapI mea
}

int Input::DeltaMouseX()
{
	return currentMouseX - previousMouseX;
}

int Input::DeltaMouseY()
{
	return currentMouseY - previousMouseY;
}

void Input::MapKeyToAction(int key, ActionType action)
{
	keyToActionMap[key] = action;
}

void Input::MapActionToKey(ActionType action, int key)
{
	actionToKeyMap[action] = key;
}

void Input::OnKeyPressed(KeyboardPressEvent& event)
{
	std::cout << "Key pressed: " << event.Key() << std::endl;
	keyMap[event.Key()] = true;
	//auto action = keyToActionMap.find(event.Key());
	//if (action != keyToActionMap.end()) {
	//	dispatcher.Dispatch(ActionEvent(action->second, true));
	//}
}

void Input::OnKeyReleased(KeyboardReleaseEvent& event)
{
	std::cout << "Key released: " << event.Key() << std::endl;
	keyMap[event.Key()] = false;
	//auto action = keyToActionMap.find(event.Key());
	//if (action != keyToActionMap.end()) {
	//	dispatcher.Dispatch(ActionEvent(action->second, false));
	//}
}

void Input::OnMouseButtonPressed(MouseButtonPressEvent& event)
{
	std::cout << "Mouse button pressed: " << event.Button() << std::endl;
	buttonMap[event.Button()] = true;
}

void Input::OnMouseButtonReleased(MouseButtonReleaseEvent& event)
{
	std::cout << "Mouse button released: " << event.Button() << std::endl;
	buttonMap[event.Button()] = false;
}

void Input::OnMouseMoved(MouseMoveEvent& event)
{
	//std::cout << "Mouse moved: " << event.MouseX() << ", " << event.MouseY() << std::endl;
	currentMouseX = event.MouseX();
	currentMouseY = event.MouseY();
}

void Input::OnEvent(Event& event)
{
    switch (event.Type()) {
        case EventType::KeyPressed:
			OnKeyPressed(static_cast<KeyboardPressEvent&>(event));
			break;
		case EventType::KeyReleased:
            OnKeyReleased(static_cast<KeyboardReleaseEvent&>(event));
			break;
		case EventType::MouseButtonPressed:
			OnMouseButtonPressed(static_cast<MouseButtonPressEvent&>(event));
            break;
        case EventType::MouseButtonReleased:
            OnMouseButtonReleased(static_cast<MouseButtonReleaseEvent&>(event));
			break;
		case EventType::MouseMoved:
			OnMouseMoved(static_cast<MouseMoveEvent&>(event));
			break;
    }
}
