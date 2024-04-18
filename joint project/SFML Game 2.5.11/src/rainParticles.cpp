#include "rainParticles.h"

RainParticle::RainParticle(float x, float y)
    : m_position(x, y), m_velocityY(400.0f), m_alive(true) {
}

void RainParticle::update(float deltaTime) {
    m_position.y += m_velocityY * deltaTime;
    // Check if particle is below screen to mark it as dead
    if (m_position.y > 1000.0f) { // Adjust 600.0f based on your screen height
        m_alive = false;
    }
}

bool RainParticle::isAlive() const {
    return m_alive;
}

sf::Vector2f RainParticle::getPosition() const {
    return m_position;
}
