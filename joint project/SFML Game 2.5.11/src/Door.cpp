#include "Door.h"

Door::Door(CurrentRoom currentRoom,DetectorPositions t_location, sf::Vector2f t_position) : location(t_location), position(t_position), m_room(currentRoom)
{
	hitbox.setFillColor(sf::Color::Transparent);
	if (location == DetectorPositions::LEFT || location == DetectorPositions::RIGHT)
	{
		hitbox.setSize(sf::Vector2f(20, 48));
		hitbox.setOrigin(10, 24);
	}
	else {
		hitbox.setSize(sf::Vector2f(48, 20));
		hitbox.setOrigin(24, 10);
	}

	hitbox.setPosition(t_position);
	
	spawnPoint.setFillColor(sf::Color::Transparent);
	spawnPoint.setSize(sf::Vector2f(20, 20));
	spawnPoint.setOrigin(10, 10);

	setSpawnPointPosition();
}

void Door::setSpawnPointPosition()
{
	if (location == DetectorPositions::LEFT) {
		spawnPoint.setPosition(hitbox.getPosition().x + 50, hitbox.getPosition().y);
	}
	if (location == DetectorPositions::RIGHT) {
		spawnPoint.setPosition(hitbox.getPosition().x - 50, hitbox.getPosition().y);
	}
	if (location == DetectorPositions::UP) {
		spawnPoint.setPosition(hitbox.getPosition().x, hitbox.getPosition().y + 50);
	}
	if (location == DetectorPositions::DOWN) {
		spawnPoint.setPosition(hitbox.getPosition().x, hitbox.getPosition().y - 50);
	}
}

bool Door::detectCollision(sf::Sprite& t_player)
{
	if (hitbox.getGlobalBounds().intersects(t_player.getGlobalBounds())) {
		return true;
	}
	return false;
}

void Door::update()
{
}

void Door::render(sf::RenderWindow& _window)
{
	_window.draw(hitbox);
	_window.draw(spawnPoint);
}

void Door::setPartner(Door* _partner)
{
	if(_partner != nullptr)
		partnerDoor = _partner;
}
