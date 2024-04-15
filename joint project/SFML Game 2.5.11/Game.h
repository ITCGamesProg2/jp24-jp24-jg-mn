
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "pickup.h"
#include "particle.h"

struct Rectangle {
	float x, y;
	float width, height;
};

class Game
{
public:
	Game();
	~Game();
	
	void run();

private:

	enum class GameState {
		MainMenu,
		Playing,
		Paused
	};

	enum class PlayerCharacter {
		None,  
		Crab,
		Fox,
		Goat
	};

	enum class Direction {
		Left,
		Right
	};

	Direction m_playerDirection;

	GameState m_gameState;
	PlayerCharacter m_playerCharacter;

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void updateAnimation();
	void updatePlayerSpriteColor(sf::Sprite& playerSprite);

	bool checkCollision(float objX, float objY, float objWidth, float objHeight, const Rectangle& rect);
	bool checkCollisions(float objX, float objY, float objWidth, float objHeight, const std::vector<Rectangle>& rectangles);

	void shoot();

	void selectCharacter(PlayerCharacter character);
	void updateButtonColor(sf::Sprite& button, const sf::Vector2f& mousePosition);
	void startPlaying();
	void handleMainMenuHover(const sf::Vector2f& mousePosition);
	void handleMainMenuClick(const sf::Vector2f& mousePosition);
	void togglePause();

	sf::Clock m_animationClock;
	float m_frameDuration;
	int m_currentFrame;

	std::vector<Projectile> m_projectiles;

	Pickup m_pickup;
	sf::Texture pickupTexture;

	std::vector<Particle> m_particles;
	void updateParticles(sf::Time deltaTime);
	void drawParticles();

	sf::Sprite m_pauseButtonSprite;
	sf::Texture m_pauseButtonTexture;

	sf::Time m_shootCooldown;
	sf::Clock m_shootTimer;

	sf::Texture m_playButtonTexture;
	sf::Sprite m_playButtonSprite;

	sf::Texture m_exitButtonTexture;
	sf::Sprite m_exitButtonSprite;

	sf::Texture m_crabTexture;
	sf::Sprite m_crabSprite;

	sf::Texture m_foxTexture;
	sf::Sprite m_foxSprite;

	sf::Texture m_goatTexture;
	sf::Sprite m_goatSprite;

	sf::Vector2f m_playerPosition;

	sf::Font font;
	sf::Text title;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Texture gameBackgroundTexture;
	sf::Sprite gameBackgroundSprite;

	sf::Texture m_tileTexture;
	sf::Sprite m_tileSprite;

	sf::Texture m_crabProjectileTexture;
    sf::Texture m_foxProjectileTexture; 
    sf::Texture m_goatProjectileTexture;


	Rectangle rect1;
	float x1 = 100.0f;
	float y1 = 200.0f;
	float width1 = 50.0f;
	float height1 = 100.0f;


	sf::RenderWindow m_window; // main SFML window
	//sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

