#include "pickup.h"

Pickup::Pickup(sf::Texture& texture)
    : m_active(false)
{
    m_sprite.setTexture(texture);
}

void Pickup::spawn(const sf::Vector2f& position)
{
    m_sprite.setPosition(position);
    m_active = true;
    m_duration = sf::seconds(3.0f); 
    m_effectTimer.restart();
}

void Pickup::draw(sf::RenderWindow& window)
{
    if (m_active)
    {
        window.draw(m_sprite);
    }
}

bool Pickup::isCollected(const sf::FloatRect& playerBounds)
{
    if (m_active)
    {
        sf::FloatRect pickupBounds = m_sprite.getGlobalBounds();
        return pickupBounds.intersects(playerBounds);
    }
    return false;
}

void Pickup::applyEffect(sf::Sprite& playerSprite)
{

    const float speedBoostFactor = 5.0f;

    m_active = false;

}

bool Pickup::isActive() const
{
    return m_active && (m_effectTimer.getElapsedTime() < m_duration);
}