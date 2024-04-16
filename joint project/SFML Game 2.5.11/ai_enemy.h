#ifndef AI_ENEMY_HPP
#define AI_ENEMY_HPP

#include <SFML/Graphics.hpp>

class AIEnemy {
public: 
	AIEnemy(float speed);
	void update(sf::Vector2f playerPosition, float deltaTime);
	void render(sf::RenderWindow& window);
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f position);

	enum class AIType {
		AI_ID_NONE,
		AI_ID_SEEK_AT_PLAYER

	};

private:
	sf::Sprite m_aiSprite;
	sf::Texture m_aiTexture;

	void setUpSprite();
	void updateAnimation();

	float speed;
};

#endif AI_ENEMY_HPP