#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include"Weapon.h"
#include"ScreenSize.h"

enum class PlayerCharacter {
    None,
    Crab,
    Fox,
    Goat
};

enum class Direction {
    Left,
    Right,
    Up,
    Down
};



class Player
{
public:
    Player();
    ~Player();

    void init(sf::Texture& t_textures, sf::Texture& t_bulletTexture);

    sf::Vector2f getPosition() { return m_playerSprite.getPosition(); };
    void setPosition(sf::Vector2f t_position) { m_playerPosition = t_position; };

    void move();
    void changeDirection();

    void update(sf::Time t_deltaTime);
    void render(sf::RenderWindow& m_window);

    void animate();

    void updatePlayerSpriteColour(bool isHit);

    void selectCharacter(PlayerCharacter t_playerCharacter);
    PlayerCharacter getSelectedCharacter() { return m_playerCharacter; };
    sf::Sprite getSprite() { return m_playerSprite; };

    int getHealth() const;
    void decreaseHealth(int amount);

    sf::Vector2f getAimDirection() const;

    bool isMoving = false;
private:
    Weapon m_weapon;

    PlayerCharacter m_playerCharacter;
    Direction m_playerDirection;
    int m_health;
   

    sf::Sprite m_playerSprite;
    sf::Vector2f m_playerPosition{100,100};
    bool isHit;

    float m_baseMovementSpeed;
    float m_movementSpeed;
    bool m_isSpeedBoosted;
    sf::Clock m_speedBoostClock;
    sf::Time m_speedBoostDuration;
    sf::Time m_speedBoostCooldown;

    //animation
    sf::Clock m_animationClock;
    float m_frameDuration{ 0.2f };
    int m_currentFrame{ 0 };
};

#endif // PLAYER_HPP

