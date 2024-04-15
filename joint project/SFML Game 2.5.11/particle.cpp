#include "Particle.h"

Particle::Particle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color, float lifetime)
    : m_position(position), m_velocity(velocity), m_color(color), m_lifetime(lifetime), m_elapsedTime(sf::Time::Zero) {
}

void Particle::update(sf::Time deltaTime) {
    m_elapsedTime += deltaTime;
    if (isAlive()) {
        m_position += m_velocity * deltaTime.asSeconds();
    }
}

void Particle::draw(sf::RenderWindow& window) const {
    if (isAlive()) {
        sf::CircleShape particleShape(1.0f);
        particleShape.setPosition(m_position);
        particleShape.setFillColor(m_color);
        window.draw(particleShape);
    }
}

bool Particle::isAlive() const {
    return m_elapsedTime.asSeconds() < m_lifetime;
}

