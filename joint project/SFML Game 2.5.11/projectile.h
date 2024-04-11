#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>

class Projectile
{
public:
    Projectile(const sf::Vector2f& position, float angle);
    ~Projectile();

    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;

private:
    sf::CircleShape m_shape;
    sf::Vector2f m_velocity;
};

#endif // PROJECTILE_HPP
