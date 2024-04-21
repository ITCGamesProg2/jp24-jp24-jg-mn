
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Candle/RadialLight.hpp"
#include <Candle/LightingArea.hpp>
#include <SFML/Audio.hpp>
#include "Projectile.h"
#include "Pickup.h"
#include "Particle.h"
#include "Player.h"
#include "ScreenSize.h"
#include "Map.h"
#include "AIenemy.h"
#include "rainParticles.h"




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
		Paused,
		GameOver,
		GameWin
	};

	GameState m_gameState;

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void loadTextures();
	void setupSprite();
	void restartGame();
	void initialize();

	void updateButtonColor(sf::Sprite& button, const sf::Vector2f& mousePosition);
	void startPlaying();
	void handleMainMenuHover(const sf::Vector2f& mousePosition);
	void handleMainMenuClick(const sf::Vector2f& mousePosition);
	void togglePause();

	void loadAudio();

	sf::Texture m_crabTexture;
	sf::Texture m_foxTexture;
	sf::Texture m_goatTexture;
	sf::Texture m_crabProjectileTexture;
	sf::Texture m_foxProjectileTexture;
	sf::Texture m_goatProjectileTexture;

	Player m_player;

	Pickup m_pickup;
	sf::Texture pickupTexture;


	std::vector<RainParticle> m_rainParticles;
	std::vector<Particle> m_particles;
	void updateParticles(sf::Time deltaTime);
	void applyParticles();
	void drawParticles();

	void createRain();
	void updateRain(float deltaTime);
	void drawRain();

	sf::Sprite m_pauseButtonSprite;
	sf::Texture m_pauseButtonTexture;

	sf::Texture m_playButtonTexture;
	sf::Sprite m_playButtonSprite;

	sf::Texture m_exitButtonTexture;
	sf::Sprite m_exitButtonSprite;

	sf::Sprite m_crabSprite;

	sf::Sprite m_foxSprite;

	sf::Sprite m_goatSprite;

	sf::Text m_healthText;

	sf::Font font;
	sf::Text title;


	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Texture gameBackgroundTexture;
	sf::Sprite gameBackgroundSprite;

	sf::Texture m_tileTexture;
	sf::Sprite m_tileSprite;
	
	sf::Music m_backgroundMusic;
	sf::Music m_menuMusic;

	candle::LightingArea fog;
	candle::RadialLight light;

	sf::Text collectedCountText;
	sf::Text notEnoughStrawberriesText;

	void spawnEnemy();
	AIenemy m_enemy;
	sf::Texture m_enemyTexture;
	sf::Vector2f m_enemyPosition;
	float m_enemySpeed;

	sf::Sprite m_winBoxSprite;
	sf::Texture m_winBoxTexture;



	Rectangle rect1;
	float x1 = 100.0f;
	float y1 = 200.0f;
	float width1 = 50.0f;
	float height1 = 100.0f;

	sf::View m_gameView;
	void setView();

	//Map
	Map m_map;

	sf::RenderWindow m_window; // main SFML window
	//sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

