#include "ai_enemy.h"

AIEnemy::AIEnemy(float speed) : speed(speed)
{
	setUpSprite();
}

void AIEnemy::update(sf::Vector2f playerPosition, float deltaTime)
{
	sf::Vector2f direction = playerPosition - m_aiSprite.getPosition();
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0)
	{
		direction /= length;
	}
	m_aiSprite.move(direction * speed * deltaTime);
} 

void AIEnemy::render(sf::RenderWindow& window)
{

}

sf::Vector2f AIEnemy::getPosition() const
{
	return sf::Vector2f();
}

void AIEnemy::setPosition(sf::Vector2f position)
{
}

void AIEnemy::setUpSprite()
{
	if (!m_aiTexture.loadFromFile("ASSETS/IMAGES/gorilla.png "));
}

void AIEnemy::updateAnimation()
{
}
