#pragma once
#include<SFML/Graphics.hpp>
#include"Door.h"
#include<iostream>
#include<vector>
#include"ScreenSize.h"
#include"Structs.h"
#include"player.h"

class Room
{
public:
	Room();
	void init(sf::Vector2f t_position);
	void update(Player& t_player);
	void render(sf::RenderWindow& t_window);
	void setUpDoors(std::vector<RoomLayout> t_layout);
	bool doorCollision(sf::Sprite& t_playerSprite);
	Door* getDoor(DetectorPositions t_doorPos);
	std::vector<Door*> getDoors() {
		return m_doors;
	};

private:
	sf::Vector2f m_position;
	sf::Sprite m_roomSprite;
	sf::Texture m_roomTexture;

	sf::View m_roomView;
	std::vector<Door*> m_doors;

};
