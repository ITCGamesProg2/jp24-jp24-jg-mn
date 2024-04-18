#ifndef AIENEMY_HPP
#define AIENEMY_HPP

#include <SFML/Graphics.hpp>

class AIenemy {
public:
    AIenemy();

    void init(sf::Texture& texture, const sf::Vector2f& position);
    void update(const sf::Vector2f& playerPosition, float speed);
    void render(sf::RenderWindow& window);
    sf::Sprite& getSprite();

private:

    void animateEnemy();
    bool m_alive = true;
    sf::Vector2f m_enemyPosition;
    sf::Sprite m_enemySprite;
    sf::IntRect m_textureRect;
    int m_frameCount;
    int m_currentFrame;
    float m_frameDuration;
    sf::Clock m_animationClock;
};

#endif // AIENEMY_HPP
