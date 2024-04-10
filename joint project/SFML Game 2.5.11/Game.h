
#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	
	void run();

private:

	enum class GameState {
		MainMenu,
		Playing
	};

	enum class PlayerCharacter {
		None,  
		Crab,
		Fox
	};

	GameState m_gameState;
	PlayerCharacter m_playerCharacter;

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void updateAnimation();


	sf::Clock m_animationClock;
	float m_frameDuration;
	int m_currentFrame;

	sf::Texture m_playButtonTexture;
	sf::Sprite m_playButtonSprite;

	sf::Texture m_exitButtonTexture;
	sf::Sprite m_exitButtonSprite;

	sf::Texture m_crabTexture;
	sf::Sprite m_crabSprite;

	sf::Texture m_foxTexture;
	sf::Sprite m_foxSprite;

	sf::Vector2f m_playerPosition;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

