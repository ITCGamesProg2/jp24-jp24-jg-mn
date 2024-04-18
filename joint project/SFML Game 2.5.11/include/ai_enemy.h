#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy();

    void init(sf::Texture& texture, const sf::Vector2f& position);
    void update(const sf::Vector2f& playerPosition, float speed);
    void render(sf::RenderWindow& window);

private:

    void animateEnemy();

    sf::Sprite m_sprite;
    sf::IntRect m_textureRect;
    int m_frameCount;           
    int m_currentFrame;         
    float m_frameDuration;    
    sf::Clock m_animationClock;
};

#endif // ENEMY_HPP
