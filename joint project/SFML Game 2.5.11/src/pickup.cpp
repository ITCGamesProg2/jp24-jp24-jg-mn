#include "Pickup.h"

Pickup::Pickup(sf::Texture& texture)
    : m_active(false),
    m_collectedCount(0)
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
      //  return pickupBounds.intersects(playerBounds);
        if (pickupBounds.intersects(playerBounds))
        {
            m_active = false; // Mark pickup as collected
            ++m_collectedCount; // Increment collected count
            return true;
        }
    }
    return false;
}

int Pickup::getCollectedCount() const
{
    return m_collectedCount;
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