#ifndef RAINPARTICLE_HPP
#define RAINPARTICLE_HPP

#include <SFML/Graphics.hpp>

class RainParticle {
public:
    RainParticle(float x, float y);

    void update(float deltaTime);
    bool isAlive() const;
    sf::Vector2f getPosition() const; // Getter for position

private:
    sf::Vector2f m_position;
    float m_velocityY;
    bool m_alive;
};

#endif // RAINPARTICLE_HPP
