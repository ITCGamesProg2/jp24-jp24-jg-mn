#include <SFML/Graphics.hpp>

class Particle {
public:
    Particle(sf::Vector2f position, sf::Vector2f velocity, sf::Color color, float lifetime);

    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window) const;

    bool isAlive() const;

private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    sf::Color m_color;
    float m_lifetime;
    sf::Time m_elapsedTime;
};


