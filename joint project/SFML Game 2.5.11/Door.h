#pragma once
#include<SFML/Graphics.hpp>
#include"Structs.h"


class Door
{
public:
	Door(CurrentRoom currentRoom,DetectorPositions _location, sf::Vector2f _position);
	void setSpawnPointPosition();
	bool detectCollision(sf::Sprite & t_player);
	void update();
	void render(sf::RenderWindow& t_window);
	void setPartner(Door* t_partner);
	Door* getPartner() { return partnerDoor; };
	
	sf::RectangleShape spawnPoint;

	DetectorPositions location;
	sf::Vector2f position;
	CurrentRoom m_room;
private:
	sf::RectangleShape hitbox;
	Door* partnerDoor;
};

