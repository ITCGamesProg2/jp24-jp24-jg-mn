#pragma once
#include<SFML/Graphics.hpp>

enum class CurrentRoom {
	Room1,
	Room2,
	Room3
};

enum DetectorPositions {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct RoomLayout {
	sf::Vector2f doorPosition;
	DetectorPositions location;
	CurrentRoom currentRoom;
};