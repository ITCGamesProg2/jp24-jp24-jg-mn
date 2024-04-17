#include "Weapon.h"

void Weapon::update(sf::Time t_deltaTime)
{
	updateProjectiles(t_deltaTime);
}



void Weapon::shoot(sf::Vector2f t_playerPosition, const sf::Vector2f& aimDirection)
{
    if (m_shootTimer.getElapsedTime() >= m_shootCooldown)
    {
        sf::Vector2f playerCenter = t_playerPosition;

        float angle = std::atan2(aimDirection.y, aimDirection.x);

        Projectile projectile(playerCenter, angle, bulletTexture);
        m_projectiles.push_back(projectile);

        m_shootTimer.restart();
    }
}

void Weapon::render(sf::RenderWindow& win)
{
	for (const auto& projectile : m_projectiles)
	{
		projectile.draw(win);
	}
}

void Weapon::init(sf::Texture& t_texture)
{
	bulletTexture = t_texture;
}

void Weapon::updateProjectiles(sf::Time t_deltaTime)
{
	for (auto it = m_projectiles.begin(); it != m_projectiles.end(); )
	{
		it->update(t_deltaTime);

		if (it->getPosition().x < 0 || it->getPosition().x > SCREEN_WIDTH ||
			it->getPosition().y < 0 || it->getPosition().y > SCREEN_HEIGHT)
		{
			it = m_projectiles.erase(it);
		}
		else
		{
			++it;
		}
	}
}
