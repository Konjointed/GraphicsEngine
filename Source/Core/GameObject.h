#pragma once

#include <iostream>
#include <map>
#include <typeindex>
#include <memory>

class GameObject {
public:
	GameObject() = default;
	GameObject(const GameObject& other) = default; 

	template <typename T>
	bool addComponent(const T& component) {
		std::cout << "Component added to object at: " << this << std::endl;
		std::type_index typeIndex = std::type_index(typeid(T));
		if (components.find(typeIndex) != components.end()) {
			std::cout << "Component already exists and cannot be added again.\n";
			return false; // Component already exists
		}
		components[typeIndex] = std::make_shared<T>(component);
		return true;
	}

	template <typename T>
	bool removeComponent() {
		std::type_index typeIndex = std::type_index(typeid(T));
		if (components.find(typeIndex) == components.end()) {
			std::cout << "Component does not exist and cannot be removed.\n";
			return false; // Component does not exist
		}
		components.erase(typeIndex);
		return true;
	}

	template <typename T>
	T* getComponent() const {
		auto it = components.find(std::type_index(typeid(T)));
		if (it != components.end()) {
			return static_cast<T*>(it->second.get());
		}
		return nullptr; // Component does not exist
	}

	template <typename T>
	bool hasComponent() const {
		return components.find(std::type_index(typeid(T))) != components.end();
	}
private:
	std::map<std::type_index, std::shared_ptr<void>> components;
};
