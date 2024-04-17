#pragma once

#include<SFML/Graphics.hpp>
#include"projectile.h"
#include"ScreenSize.h"

class Weapon
{
public:
	void update(sf::Time t_deltaTime);
	void shoot(sf::Vector2f t_playerPosition, const sf::Vector2f& aimDirection);
	void render(sf::RenderWindow& win);
	void init(sf::Texture& t_texture);
private:
	sf::Texture bulletTexture;
	//weapon 
	sf::Time m_shootCooldown{ sf::seconds(0.3f) };
	sf::Clock m_shootTimer;
	std::vector<Projectile> m_projectiles;
	void updateProjectiles(sf::Time t_deltaTime);

};

