#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& position, float angle, const sf::Texture& texture)
    : m_rotationAngle(angle)
{
    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);
    m_sprite.setScale(sf::Vector2f(2, 2));
    m_sprite.setRotation(angle * (180.f / 3.14159f));

    float speed = 500.f;
    m_velocity.x = speed * std::cos(angle);
    m_velocity.y = speed * std::sin(angle);
}

Projectile::~Projectile()
{
}

void Projectile::update(sf::Time deltaTime)
{
    // Update projectile position
    m_sprite.move(m_velocity * deltaTime.asSeconds());

    m_rotationAngle += 360.f * deltaTime.asSeconds();
    m_sprite.setRotation(m_rotationAngle);
}

void Projectile::draw(sf::RenderWindow& window) const
{
    window.draw(m_sprite);
}

sf::Vector2f Projectile::getPosition() const
{ 
    return m_sprite.getPosition();
}
