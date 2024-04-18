#pragma once
#include<SFML/Graphics.hpp>
#include"Room.h"
#include<iostream>
#include<vector>
#include"Structs.h"
#include"player.h"



class Map
{
public:
	Map();
	void init();
	void render(sf::RenderWindow& t_window);
	void update(Player & t_playerSprite);

private:
	CurrentRoom m_currentRoom = CurrentRoom::Room1;

	std::vector<RoomLayout> m_baseRoomLayout;
	Room m_baseRoom;

	std::vector<RoomLayout> m_secondRoomLayout;
	Room m_secondRoom;

	std::vector <RoomLayout> m_thirdRoomLayout;
	Room m_thirdRoom;

	void linkDoors();
};

