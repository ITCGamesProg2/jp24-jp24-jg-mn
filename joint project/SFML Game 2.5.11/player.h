#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();
    ~Player();

    void update(sf::Time t_deltaTime);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

private:
    sf::Vector2f m_position;
    float m_movementSpeed;
};

#endif // PLAYER_HPP

