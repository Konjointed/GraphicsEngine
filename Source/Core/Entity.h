#pragma once

struct Entity {
	unsigned int id;

	bool operator==(const Entity& other) const {
		return id == other.id;
	}
};

