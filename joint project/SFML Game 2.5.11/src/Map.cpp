#include "Map.h"

Map::Map()
{
	init();
}

void Map::init()
{
	m_currentRoom = CurrentRoom::Room1;

	m_baseRoom.init(sf::Vector2f(0,0),0);
	m_secondRoom.init(sf::Vector2f(1000, 0),1); //set up third room

	RoomLayout tempDoor = RoomLayout{sf::Vector2f(698,576), DetectorPositions::UP , CurrentRoom::Room1};
	m_baseRoomLayout.push_back(tempDoor);
	m_baseRoom.setUpDoors(m_baseRoomLayout);

	RoomLayout temp1{ sf::Vector2f(1312,624),DetectorPositions::DOWN, CurrentRoom::Room2 }; //add another tempdoor but ,make it up and set at stairs
	m_secondRoomLayout.push_back(temp1);
	m_secondRoom.setUpDoors(m_secondRoomLayout);

	//set up a door for room 3

	linkDoors();

}

void Map::render(sf::RenderWindow& t_window)
{
	switch (m_currentRoom) {
	case CurrentRoom::Room1:
		m_baseRoom.render(t_window);
		break;
	case CurrentRoom::Room2:
		m_secondRoom.render(t_window);
		break;
	case CurrentRoom::Room3:
		break;
	}
}

void Map::update(Player& t_player)
{
	switch (m_currentRoom) {
	case CurrentRoom::Room1:
		m_baseRoom.update(t_player);
		for (int i = 0; i < m_baseRoom.getDoors().size(); i++) {
			if (m_baseRoom.getDoors()[i]->detectCollision(t_player.getSprite()))
			{
				t_player.setPosition(m_baseRoom.getDoors()[i]->getPartner()->spawnPoint.getPosition());
				m_currentRoom = m_baseRoom.getDoors()[i]->getPartner()->m_room;
			}
		}
		break;
	case CurrentRoom::Room2:
		m_secondRoom.update(t_player);
		for (int i = 0; i < m_secondRoom.getDoors().size(); i++) {
			if (m_secondRoom.getDoors()[i]->detectCollision(t_player.getSprite()))
			{
				t_player.setPosition(m_secondRoom.getDoors()[i]->getPartner()->spawnPoint.getPosition());
				m_currentRoom = m_secondRoom.getDoors()[i]->getPartner()->m_room;
			}
		}
		break;
	case CurrentRoom::Room3:
		break;
	}
}

void Map::linkDoors()
{
	m_baseRoom.getDoor(DetectorPositions::UP)->setPartner(m_secondRoom.getDoor(DetectorPositions::DOWN));
	m_secondRoom.getDoor(DetectorPositions::DOWN)->setPartner(m_baseRoom.getDoor(DetectorPositions::UP));

	//link top door from room 2 to bottom door from room 3 and vice versa
}



