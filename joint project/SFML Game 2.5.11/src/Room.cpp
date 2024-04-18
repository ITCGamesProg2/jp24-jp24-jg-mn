#include "Room.h"

Room::Room()
{
}

void Room::init(sf::Vector2f t_position, int t_roomNumber) 
{
	
	switch (t_roomNumber) {
	case 0:
		if (!m_roomTexture.loadFromFile("ASSETS\\IMAGES\\main_floor.png"))
		{
			std::cout << "Problem loading main floor" << std::endl;
		}
		m_grid.generateGrid(0, t_position.x);
		break;
	case 1:
		if (!m_roomTexture.loadFromFile("ASSETS\\IMAGES\\secondFLoor.png"))
		{
			std::cout << "Problem loading second floor" << std::endl;
		}
		m_grid.generateGrid(1, t_position.x);
		break;
	case 2:
		if (!m_roomTexture.loadFromFile("ASSETS\\IMAGES\\thirdFloor.png"))
		{
			std::cout << "Problem loading third floor" << std::endl;
		}
		m_grid.generateGrid(2, t_position.x);
		break;
	}
	m_roomSprite.setTexture(m_roomTexture);
	m_roomSprite.setPosition(t_position);
	m_roomSprite.setScale(1.5, 1.5); // keep scale

	m_roomView.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_roomView.setCenter(m_roomSprite.getPosition().x + (SCREEN_WIDTH / 2), m_roomSprite.getPosition().y + (SCREEN_HEIGHT / 2));

	
}

void Room::update(Player& t_player)
{
	
}

void Room::render(sf::RenderWindow& t_window)
{
	t_window.setView(m_roomView);
	t_window.draw(m_roomSprite);
	m_grid.render(t_window);
	for (int i = 0; i < m_doors.size(); i++) {
		m_doors[i]->render(t_window);
	}
}

void Room::setUpDoors(std::vector<RoomLayout> t_layout)
{
	for (const RoomLayout layout : t_layout) {
		Door* temp = new Door(layout.currentRoom,layout.location, layout.doorPosition);
		m_doors.push_back(temp);
	}
}

bool Room::doorCollision(sf::Sprite& t_playerSprite)
{
	for (int i = 0; i < m_doors.size(); i++) {
		if (m_doors[i]->detectCollision(t_playerSprite))
		{
			return true;
		}
	}
	return false;
}

Door* Room::getDoor(DetectorPositions t_doorPos)
{
	for (auto door : m_doors)
	{
		if (door->location == t_doorPos)
		{
			return door;
		}
	}
	return nullptr;
}
