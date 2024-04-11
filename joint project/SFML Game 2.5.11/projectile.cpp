#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& position, float angle)
{
    m_shape.setRadius(5.f);
    m_shape.setFillColor(sf::Color::Red);
    m_shape.setPosition(position);

    // Calculate velocity based on angle (convert angle to radians)
    float speed = 500.f; // Adjust speed as needed
    m_velocity.x = speed * std::cos(angle);
    m_velocity.y = speed * std::sin(angle);
}

Projectile::~Projectile()
{
}

void Projectile::update(sf::Time deltaTime)
{
    // Update projectile position
    m_shape.move(m_velocity * deltaTime.asSeconds());
}

void Projectile::draw(sf::RenderWindow& window) const
{
    window.draw(m_shape);
}

sf::Vector2f Projectile::getPosition() const
{
    return m_shape.getPosition();
}
