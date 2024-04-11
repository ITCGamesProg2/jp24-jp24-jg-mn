#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>

class Projectile
{
public:
    Projectile(const sf::Vector2f& position, float angle, const sf::Texture& texture);
    ~Projectile();

    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;

private:
    sf::Sprite m_sprite;
    sf::Vector2f m_velocity;
};

#endif // PROJECTILE_HPP
