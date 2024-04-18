#include "rainParticles.h"

RainParticle::RainParticle(float x, float y)
    : m_position(x, y), m_velocityY(400.0f), m_alive(true) {
}

void RainParticle::update(float deltaTime) {
    m_position.y += m_velocityY * deltaTime;
    if (m_position.y > 900.0f) { 
        m_alive = false;
    }
}

bool RainParticle::isAlive() const {
    return m_alive;
}

sf::Vector2f RainParticle::getPosition() const {
    return m_position;
}
