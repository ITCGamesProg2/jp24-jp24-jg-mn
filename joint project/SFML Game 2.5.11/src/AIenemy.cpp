#include "AIenemy.h"
#include <cmath>

AIenemy::AIenemy() {}

void AIenemy::init(sf::Texture& texture, const sf::Vector2f& position) {
    m_sprite.setTexture(texture);
    m_sprite.setPosition(position);

    m_textureRect = sf::IntRect(0, 0, 64, 64);
    m_frameCount = 8;
    m_currentFrame = 0;
    m_frameDuration = 0.2f;

    int frameWidth = texture.getSize().x / m_frameCount;
    int frameHeight = texture.getSize().y;
    m_textureRect = sf::IntRect(0, 0, frameWidth, frameHeight);
    m_sprite.setTextureRect(m_textureRect);
}

void AIenemy::update(const sf::Vector2f& playerPosition, float speed) {

    sf::Vector2f direction = playerPosition - m_sprite.getPosition();
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance != 0) {
        direction /= distance;
    }

    m_sprite.move(direction * speed);

    animateEnemy();
}



void AIenemy::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
    m_sprite.setScale(2, 2);
}

sf::Sprite& AIenemy::getSprite() {
    return m_sprite;
}

void AIenemy::animateEnemy() {
    if (m_animationClock.getElapsedTime().asSeconds() >= m_frameDuration) {
        m_animationClock.restart();


        m_currentFrame = (m_currentFrame + 1) % m_frameCount;


        int frameWidth = m_sprite.getTexture()->getSize().x / m_frameCount;


        m_textureRect.left = m_currentFrame * frameWidth;
        m_sprite.setTextureRect(m_textureRect);
    }
}


