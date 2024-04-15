#include "player.h"

Player::Player() :
    m_position(0.0f, 0.0f),
    m_movementSpeed(2.0f)
{
}

Player::~Player()
{
}

void Player::update(sf::Time t_deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_position.y -= m_movementSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_position.y += m_movementSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_position.x -= m_movementSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_position.x += m_movementSpeed;
    }
}

void Player::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}

sf::Vector2f Player::getPosition() const
{
    return m_position;
}
