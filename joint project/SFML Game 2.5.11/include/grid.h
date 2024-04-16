#pragma once
#include<SFML/Graphics.hpp>
#include<vector>

class cell {
public:
	cell(sf::Vector2f t_position) {
		cellShape.setPosition(t_position);
		cellShape.setSize(sf::Vector2f(50,40)); //our grid size
		cellShape.setFillColor(sf::Color::Transparent);
		cellShape.setOutlineThickness(1);
		cellShape.setOutlineColor(sf::Color::Blue);
	};
	sf::RectangleShape cellShape;
};

class grid {
public:
	void generateGrid()
	{
		for (int i = 0; i < 15; i++) { //15 cells long
			for (int j = 0; j < 16; j++) //16 grids long
			{
				m_cells.push_back(cell(sf::Vector2f(j * 50, i * 40))); //set positions
			}
		}
	};
	void render(sf::RenderWindow& t_window)
	{
		for (auto cell : m_cells) {
			t_window.draw(cell.cellShape);
		}
	};
private:
	std::vector<cell> m_cells;

};