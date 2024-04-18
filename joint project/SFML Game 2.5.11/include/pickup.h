#ifndef PICKUP_HPP
#define PICKUP_HPP

#include <SFML/Graphics.hpp>

class Pickup
{
public:
    Pickup(sf::Texture& texture);

    void spawn(const sf::Vector2f& position);
    void draw(sf::RenderWindow& window);
    bool isCollected(const sf::FloatRect& playerBounds);

    void applyEffect(sf::Sprite& playerSprite);
    bool isActive() const;

    int getCollectedCount() const;

private:
    sf::Sprite m_sprite;
    bool m_active;
    sf::Clock m_effectTimer;
    sf::Time m_duration;
    int m_collectedCount;
};

#endif // PICKUP_HPP
