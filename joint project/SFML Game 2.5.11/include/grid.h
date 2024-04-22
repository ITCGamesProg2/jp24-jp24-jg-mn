#pragma once
#include<SFML/Graphics.hpp>
#include"CollisionData.h"
#include<vector>



class cell {
public:
	cell(sf::Vector2f t_position) {
		cellShape.setPosition(t_position);
		cellShape.setSize(sf::Vector2f(48,48)); 
		cellShape.setFillColor(sf::Color::Transparent);
		cellShape.setOutlineThickness(1);
		cellShape.setOutlineColor(sf::Color::White);
	};
	void setRed() {
		cellShape.setFillColor(sf::Color::Red);
	}
	sf::RectangleShape cellShape;
};

class grid {
public:
	void generateGrid(int t_obs, int t_x) 
	{
		int temp = 0;
		for (int i = 0; i < 19; i++) { //15 cells long
			for (int j = 0; j < 25; j++) //16 grids long
			{
				m_cells.push_back(cell(sf::Vector2f(t_x + j * 48, i * 48))); 
				switch (t_obs) {
				case 0:
					if (roomOne[temp] == 333) {
						//m_obstacleCells.push_back(m_cells.at(temp));
						//m_cells.at(temp).setRed();
					}
					break;
				case 1:
					if (roomOne[temp] == 333) {
						//m_obstacleCells.push_back(m_cells.at(temp));
						//m_cells.at(temp).setRed();
					}
					break;
				case 2:
					if (roomOne[temp] == 333) {
						//m_obstacleCells.push_back(m_cells.at(temp));
						//m_cells.at(temp).setRed();
					}
					break;
				}
				temp++;
				
			}
		}
	};
	void render(sf::RenderWindow& t_window)
	{
		for (auto cell : m_cells) {
			//t_window.draw(cell.cellShape);
		}
	};
private:
	std::vector<cell> m_cells;
	std::vector<cell> m_obstacleCells;

};