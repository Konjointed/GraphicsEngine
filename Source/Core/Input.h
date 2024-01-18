#pragma once

#include <unordered_map>

#include "../Events/IEventHandler.h"

class EventDispatcher;
class KeyboardPressEvent;
class KeyboardReleaseEvent;
class MouseMoveEvent;
class MouseButtonPressEvent;
class MouseButtonReleaseEvent;

enum class ActionType {
	Jump,
	MoveLeft,
	MoveRight,
	MoveForward,
	MoveBackward,
};

class Input : public IEventHandler {
public:
	Input(EventDispatcher& dispatcher);
	~Input();

	void EndFrame();

	bool IsKeyDown(int key);
	bool IsMouseButtonDown(int button);

	int DeltaMouseX();
	int DeltaMouseY();

	void OnEvent(Event& event) override;
private:
	void MapKeyToAction(int key, ActionType action);
	void MapActionToKey(ActionType action, int key);
	void OnKeyPressed(KeyboardPressEvent& event);
	void OnKeyReleased(KeyboardReleaseEvent& event);
	void OnMouseButtonPressed(MouseButtonPressEvent& event);
	void OnMouseButtonReleased(MouseButtonReleaseEvent& event);
	void OnMouseMoved(MouseMoveEvent& event);
private:
	int currentMouseX = 0, currentMouseY = 0;
	int previousMouseX = 0, previousMouseY = 0;

	EventDispatcher& dispatcher;

	std::unordered_map<int, bool> keyMap;
	std::unordered_map<int, bool> buttonMap;
	std::unordered_map<ActionType, int> actionToKeyMap;
	std::unordered_map<int, ActionType> keyToActionMap;
};
