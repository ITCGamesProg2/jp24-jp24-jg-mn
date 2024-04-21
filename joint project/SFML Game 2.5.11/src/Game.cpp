/// @author Monika Nusi and katrina Gorska
/// @date 09/04/2024


#include "Game.h"
#include <iostream>
#include <sstream>



Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "SFML Game" },
	m_exitGame{ false }, 
	m_gameState(GameState::MainMenu),
	m_pickup(pickupTexture),
	fog(candle::LightingArea::FOG, sf::Vector2f(-SCREEN_HEIGHT, -SCREEN_WIDTH) ,sf::Vector2f(SCREEN_WIDTH * 5,SCREEN_HEIGHT* 5)),
	m_enemySpeed(1.5f)
{
	fog.setAreaColor(sf::Color::Black);
	light.setRange(600);
	light.setIntensity(0.5);
	light.setColor(sf::Color(255,140,0,150));
		
	loadTextures();
	setupFontAndText(); 
	setupSprite();
	loadAudio();

	spawnEnemy();

	std::vector<Rectangle> buildings;
	buildings.push_back(rect1);
	buildings.push_back(Rectangle{ x1, y1, width1, height1 }); 
	setupFontAndText();  
	setupSprite(); 

	initialize();
}

Game::~Game()
{

}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			if (m_gameState == GameState::Playing)
			{
				update(timePerFrame);
			}
		}
		if (m_exitGame)
		{
			m_window.close();
		}

		render();
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (newEvent.type == sf::Event::Closed)
		{
			m_exitGame = true;
		}
		else if (m_gameState == GameState::MainMenu)
		{
			if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Left)
			{
				handleMainMenuClick(sf::Vector2f(newEvent.mouseButton.x, newEvent.mouseButton.y));
			}
			else if (newEvent.type == sf::Event::MouseMoved)
			{
				handleMainMenuHover(sf::Vector2f(newEvent.mouseMove.x, newEvent.mouseMove.y));
			}
		}

		else if (m_gameState == GameState::Playing || m_gameState == GameState::Paused)
		{
			if (newEvent.type == sf::Event::MouseButtonPressed && newEvent.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mousePosition = sf::Vector2f(newEvent.mouseButton.x, newEvent.mouseButton.y);
				if (m_pauseButtonSprite.getGlobalBounds().contains(mousePosition))
				{
					togglePause();
				}
			}
			else if (newEvent.type == sf::Event::KeyReleased && newEvent.key.code == sf::Keyboard::Escape)
			{
				togglePause();
			}
		}
	}
}

void Game::loadTextures()
{
	if (!m_crabProjectileTexture.loadFromFile("ASSETS\\IMAGES\\cheese.png"))
	{
		std::cout << "Problem loading crab projectile texture" << std::endl;
	}

	if (!m_foxProjectileTexture.loadFromFile("ASSETS\\IMAGES\\snowball.png"))
	{
		std::cout << "Problem loading fox projectile texture" << std::endl;
	}

	if (!m_goatProjectileTexture.loadFromFile("ASSETS\\IMAGES\\cheese.png"))
	{
		std::cout << "Problem loading goat projectile texture" << std::endl;
	}

	if (!pickupTexture.loadFromFile("ASSETS\\IMAGES\\strawberry.png"))
	{
		std::cout << "Problem loading pickup texture" << std::endl;
		return;
	}
	if (!m_crabTexture.loadFromFile("ASSETS\\IMAGES\\crabSpritesheet.png"))
	{
		std::cout << "Problem loading spritesheet" << std::endl;
		return;
	}
	if (!m_foxTexture.loadFromFile("ASSETS\\IMAGES\\foxSpritesheet.png"))
	{
		std::cout << "Problem loading spritesheet" << std::endl;
		return;
	}
	if (!m_goatTexture.loadFromFile("ASSETS\\IMAGES\\goatSpritesheet.png"))
	{
		std::cout << "Problem loading spritesheet" << std::endl;
		return;
	}
	if (!m_crabProjectileTexture.loadFromFile("ASSETS\\IMAGES\\starfish.png"))
	{
		std::cout << "Problem loading crab projectile texture" << std::endl;
	}

	if (!m_foxProjectileTexture.loadFromFile("ASSETS\\IMAGES\\snowball.png"))
	{
		std::cout << "Problem loading fox projectile texture" << std::endl;
	}

	if (!m_goatProjectileTexture.loadFromFile("ASSETS\\IMAGES\\cheese.png"))
	{
		std::cout << "Problem loading goat projectile texture" << std::endl;
	}

	if (!m_enemyTexture.loadFromFile("ASSETS\\IMAGES\\gorillaspritesheet.png")) 
	{
		std::cout << "Problem loading enemy texture" << std::endl;
	}

	if (!m_winBoxTexture.loadFromFile("ASSETS\\IMAGES\\stawberry2.png"))
	{
		std::cout << "Error loading win box texture!" << std::endl;
	}

}


void Game::togglePause()
{
	if (m_gameState == GameState::Playing)
	{
		m_gameState = GameState::Paused;
		std::cout << "Game Paused" << std::endl;
	}
	else if (m_gameState == GameState::Paused)
	{
		m_gameState = GameState::Playing;
		std::cout << "Game Resumed" << std::endl;
	}
}

void Game::setView()
{
	m_gameView.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::handleMainMenuClick(const sf::Vector2f& mousePosition)
{
	if (m_exitButtonSprite.getGlobalBounds().contains(mousePosition))
	{
		std::cout << "Exiting Game!" << std::endl;
		m_exitGame = true;
	}
	else if (m_crabSprite.getGlobalBounds().contains(mousePosition))
	{
		m_player.selectCharacter(PlayerCharacter::Crab);
		m_player.init(m_crabTexture, m_crabProjectileTexture);
	}
	else if (m_foxSprite.getGlobalBounds().contains(mousePosition))
	{
		m_player.selectCharacter(PlayerCharacter::Fox);
		m_player.init(m_foxTexture, m_foxProjectileTexture);
	}
	else if (m_goatSprite.getGlobalBounds().contains(mousePosition))
	{
		m_player.selectCharacter(PlayerCharacter::Goat);
		m_player.init(m_goatTexture, m_goatProjectileTexture);
	}
	else if (m_playButtonSprite.getGlobalBounds().contains(mousePosition))
	{
		if (m_player.getSelectedCharacter() != PlayerCharacter::None)
		{
			startPlaying();
		}
		else
		{
			std::cout << "Please select a character first!" << std::endl;
		}
	}
}

void Game::handleMainMenuHover(const sf::Vector2f& mousePosition)
{
	updateButtonColor(m_playButtonSprite, mousePosition);
	updateButtonColor(m_exitButtonSprite, mousePosition);
	updateButtonColor(m_crabSprite, mousePosition);																							
	updateButtonColor(m_foxSprite, mousePosition);
	updateButtonColor(m_goatSprite, mousePosition);
}

void Game::updateButtonColor(sf::Sprite& button, const sf::Vector2f& mousePosition)
{
	if (button.getGlobalBounds().contains(mousePosition))
	{
		button.setColor(sf::Color(200, 200, 200));
	}
	else
	{
		button.setColor(sf::Color::White);
	}
}

void Game::startPlaying()
{
	m_gameState = GameState::Playing;
	std::cout << "Starting Game!" << std::endl;
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}


void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if (m_gameState == GameState::Playing)
	{
		setView(); // load view

		sf::FloatRect playerBounds = m_player.getSprite().getGlobalBounds();
		sf::FloatRect enemyBounds = m_enemy.getSprite().getGlobalBounds();
		sf::FloatRect winBoxBounds = m_winBoxSprite.getGlobalBounds();

		int collectedCount = m_pickup.getCollectedCount();
		collectedCountText.setString("Strawberries collected: " + std::to_string(collectedCount) + " /10");
		//std::string message = "Strawberries collected: " + std::to_string(collectedCount) + " / 10";
		if (m_pickup.isCollected(m_player.getSprite().getGlobalBounds()))
		{
			//m_pickup.applyEffect(m_player.getSprite());

			m_pickup.spawn(sf::Vector2f(rand() % 700 + 50, rand() % 500 + 50));
		}

		if (playerBounds.intersects(winBoxBounds) && collectedCount >= 10) 
		{
			std::cout << "You win!" << std::endl;
		
			m_gameState = GameState::GameWin;
		}
		else if (playerBounds.intersects(winBoxBounds) && collectedCount < 10) 
		{
			std::cout << "go back not enough strawberries!" << std::endl;
		}

		std::stringstream ss;
		ss << "Health: " << m_player.getHealth();
		m_healthText.setString(ss.str());

		if (playerBounds.intersects(enemyBounds))
		{
			int damageAmount = 1;
			m_player.decreaseHealth(damageAmount);

			std::cout << "Player's remaining health: " << m_player.getHealth() << std::endl;

			if (m_player.getHealth() <= 0)
			{
				std::cout << "Game over." << std::endl;
				m_gameState = GameState::GameOver;
			}
			 
			m_player.updatePlayerSpriteColour(true);
		}
		else {
			m_player.updatePlayerSpriteColour(false);

	        
		}

		light.setPosition(m_player.getPosition());

		m_enemy.update(m_player.getPosition(), m_enemySpeed);
		
		m_player.update(t_deltaTime);
		m_map.update(m_player);
		applyParticles();
		createRain();
		updateRain(t_deltaTime.asSeconds());
		updateParticles(t_deltaTime);
	}
}

void Game::updateParticles(sf::Time deltaTime) {
	for (auto it = m_particles.begin(); it != m_particles.end();) {
		it->update(deltaTime);
		if (!it->isAlive()) {
			it = m_particles.erase(it);
		}
		else {
			++it;
		}

		m_map.update(m_player);
	}
}

void Game::applyParticles()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A)||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S)||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		for (int i = 0; i < 5; ++i) {
			sf::Vector2f randomOffset = sf::Vector2f((rand() % 10) - 5, (rand() % 10) - 5);
			sf::Vector2f particlePosition = m_player.getPosition()  + randomOffset;
			sf::Vector2f randomVelocity = sf::Vector2f((rand() % 100) - 50, (rand() % 100) - 50);
			sf::Color particleColor = sf::Color::Black;
			float lifetime = 0.2;
			Particle particle(particlePosition, randomVelocity, particleColor, lifetime);
			m_particles.push_back(particle);
		}
	}
}

void Game::drawParticles() {
	for (const auto& particle : m_particles) {
		particle.draw(m_window);
	}
}

void Game::updateRain(float deltaTime) {
	// Update rain particles
	for (auto& rain : m_rainParticles) {
		rain.update(deltaTime);
	}
	// Remove dead rain particles
	m_rainParticles.erase(std::remove_if(m_rainParticles.begin(), m_rainParticles.end(),
		[](const RainParticle& rain) { return !rain.isAlive(); }), m_rainParticles.end());
}

void Game::createRain() {
	// Create new rain particles
	for (int i = 0; i < 10; ++i) {
		float startX = static_cast<float>(rand() % 1175);
		float startY = static_cast<float>(rand() % 200 - 100);
		m_rainParticles.emplace_back(startX, startY);
	}
}


void Game::drawRain() {
	// Draw rain particles
	sf::VertexArray lines(sf::Lines);
	for (const auto& rain : m_rainParticles) {
		sf::Vector2f endPos = rain.getPosition() + sf::Vector2f(0.0f, 10.0f); // Raindrop length
		lines.append(sf::Vertex(rain.getPosition(), sf::Color::Blue));
		lines.append(sf::Vertex(endPos, sf::Color::Blue));
	}
	m_window.draw(lines);
}

void Game::render()
{
	fog.clear();
	fog.draw(light);
	fog.display();
	m_window.clear(sf::Color::White);

	
	if (m_gameState == GameState::MainMenu)
	{
		m_window.draw(backgroundSprite);
		m_window.draw(m_tileSprite);
		m_window.draw(m_playButtonSprite);
		m_window.draw(m_exitButtonSprite);
		m_window.draw(m_crabSprite);
		m_window.draw(m_foxSprite);
		m_window.draw(m_goatSprite);
		m_window.draw(title);

		
		sf::Text selectedCharacterText;
		selectedCharacterText.setFont(font);
		selectedCharacterText.setCharacterSize(30);
		selectedCharacterText.setFillColor(sf::Color::White);
		selectedCharacterText.setOutlineColor(sf::Color::Black);
		selectedCharacterText.setOutlineThickness(2);

		if (m_player.getSelectedCharacter() == PlayerCharacter::Crab)
		{
			selectedCharacterText.setString("Selected Character: Crab");
		}
		else if (m_player.getSelectedCharacter() == PlayerCharacter::Fox)
		{
			selectedCharacterText.setString("Selected Character: Fox");
		}
		else if (m_player.getSelectedCharacter() == PlayerCharacter::Goat)
		{
			selectedCharacterText.setString("Selected Character: Goat");
		}
		else
		{
			selectedCharacterText.setString("Selected Character:");
		}

		selectedCharacterText.setPosition(500.0f, 230.0f);
		m_window.draw(selectedCharacterText);
	}
	else if (m_gameState == GameState::Playing)
	{
		m_map.render(m_window);

		drawParticles();

		//Player drawings
		m_player.render(m_window);
		//Pickups
 	    m_pickup.draw(m_window);

		drawRain();
		
		//m_window.setView(m_gameView);

		//sf::Vector2f worldPos = m_window.mapPixelToCoords(m_player.getPosition(),m_gameView);
	    //m_player.setPosition(worldPos);

		m_enemy.render(m_window);

	
		m_window.draw(m_winBoxSprite);

		m_window.draw(fog);
		m_window.draw(light);
		
		m_window.draw(m_pauseButtonSprite);
		m_window.draw(m_healthText);
		m_window.draw(collectedCountText);
	}
	else if (m_gameState == GameState::Paused)
	{
		m_window.draw(m_pauseButtonSprite);

		sf::Text pauseText;
		pauseText.setFont(font); 
		pauseText.setString("Game Paused");
		pauseText.setPosition(250.0f, 250.0f);
		pauseText.setCharacterSize(100U);
		pauseText.setFillColor(sf::Color::Black);

		m_window.draw(pauseText);

	}
	else if (m_gameState == GameState::GameOver) 
	{
		sf::Texture m_gameOverTexture;
		if (!m_gameOverTexture.loadFromFile("ASSETS\\IMAGES\\background.gif"))
		{
			std::cout << "error loading gameover background";
		}
		sf::Sprite m_gameOVerSprite;
		m_gameOVerSprite.setTexture(m_gameOverTexture);
		m_gameOVerSprite.setScale(static_cast<float>(SCREEN_WIDTH) / m_gameOVerSprite.getLocalBounds().width,
			static_cast<float>(SCREEN_HEIGHT) / m_gameOVerSprite.getLocalBounds().height);
		m_window.draw(m_gameOVerSprite);

		sf::Text gameOverText;
		gameOverText.setFont(font);
		gameOverText.setString("Game Over!");
		gameOverText.setCharacterSize(180);
		gameOverText.setOutlineColor(sf::Color::White);
		gameOverText.setOutlineThickness(2);
		gameOverText.setFillColor(sf::Color::Red);

		gameOverText.setPosition(400, 300);

		sf::Text quitText;
		quitText.setFont(font);
		quitText.setString("Press Q to quit");
		quitText.setCharacterSize(80);
		quitText.setFillColor(sf::Color::White);
		quitText.setOutlineColor(sf::Color::Black);
		quitText.setOutlineThickness(2);
		quitText.setPosition(475, 500);

		sf::Text restartText;
		restartText.setFont(font);
		restartText.setString("Press R to restart");
		restartText.setCharacterSize(80);
		restartText.setFillColor(sf::Color::White);
		restartText.setOutlineColor(sf::Color::Black);
		restartText.setOutlineThickness(2);
		restartText.setPosition(450, 600);

		m_window.draw(gameOverText);
		m_window.draw(quitText);
		m_window.draw(restartText);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			m_window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			restartGame();
		}
	}
	else if (m_gameState == GameState::GameWin)
	{

		sf::Texture m_gameWinTexture;
		if (!m_gameWinTexture.loadFromFile("ASSETS\\IMAGES\\backgroundq.gif"))
		{
			std::cout << "error loading gameover background";
		}
		sf::Sprite m_gameWinSprite;
		m_gameWinSprite.setTexture(m_gameWinTexture);
		m_gameWinSprite.setScale(static_cast<float>(SCREEN_WIDTH) / m_gameWinSprite.getLocalBounds().width,
			static_cast<float>(SCREEN_HEIGHT) / m_gameWinSprite.getLocalBounds().height);
		m_window.draw(m_gameWinSprite);

		sf::Text gameWinText;
		gameWinText.setFont(font);
		gameWinText.setString("YOU WON!");
		gameWinText.setCharacterSize(180);
		gameWinText.setFillColor(sf::Color::Black);
		gameWinText.setPosition(2300, 200);


		sf::Text quitText;
		quitText.setFont(font);
		quitText.setString("Press Q to quit");
		quitText.setCharacterSize(80);
		quitText.setFillColor(sf::Color::Blue);
		quitText.setPosition(2470, 300);

		sf::Text restartText;
		restartText.setFont(font);
		restartText.setString("Press R to restart");
		restartText.setCharacterSize(80);
		restartText.setFillColor(sf::Color::Blue);
		restartText.setPosition(2450, 400);

		m_window.draw(gameWinText);
		m_window.draw(quitText);
		m_window.draw(restartText);
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			m_window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			restartGame();
		}
		
	}
	m_window.display();
}


void Game::setupFontAndText()
{
	if (!font.loadFromFile("ASSETS\\FONTS\\font.otf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	title.setFont(font);
	title.setString("Wildlife Warfare");
	title.setPosition(400.0f, 40.0f);
	title.setCharacterSize(100U);
	title.setFillColor(sf::Color::White);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(2);


	m_healthText.setFont(font);
	m_healthText.setCharacterSize(24);
	m_healthText.setFillColor(sf::Color::White);
	m_healthText.setPosition(10.f, 10.f);

	
	collectedCountText.setFont(font);
	collectedCountText.setCharacterSize(24);
	collectedCountText.setFillColor(sf::Color::White);
	collectedCountText.setPosition(10.f, 40.f); 

}


void Game::setupSprite()
{
	m_crabSprite.setTexture(m_crabTexture);
	m_crabSprite.setPosition(490.0f, 165.0f);
	m_crabSprite.setScale(3.0f, 3.0f);
	m_crabSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

	m_foxSprite.setTexture(m_foxTexture);
	m_foxSprite.setPosition(560.0f, 165.0f);
	m_foxSprite.setScale(3.0f, 3.0f);
	m_foxSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

	m_goatSprite.setTexture(m_goatTexture);
	m_goatSprite.setPosition(640.0f, 165.0f);
	m_goatSprite.setScale(3.0f, 3.0f);
	m_goatSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

	m_winBoxSprite.setTexture(m_winBoxTexture);
	m_winBoxSprite.setPosition(2900,270);
	m_winBoxSprite.setScale(1,1);

	m_pickup = Pickup(pickupTexture);
	sf::Vector2f randomPosition = sf::Vector2f(rand() % 700 + 50, rand() % 500 + 50);
	m_pickup.spawn(randomPosition);

	if (!m_pauseButtonTexture.loadFromFile("ASSETS\\IMAGES\\pause.png"))
	{
		std::cout << "Problem loading pause button texture" << std::endl;
	}
	m_pauseButtonSprite.setTexture(m_pauseButtonTexture);
	m_pauseButtonSprite.setPosition(1100.0f, 10.0f);
	m_pauseButtonSprite.setScale(sf::Vector2f(2, 2));
	
	if (!m_playButtonTexture.loadFromFile("ASSETS\\IMAGES\\play.png"))
	{
		std::cout << "Problem loading play button texture" << std::endl;
	}
	m_playButtonSprite.setTexture(m_playButtonTexture);
	m_playButtonSprite.setPosition(400.0f, 250.0f);
	m_playButtonSprite.setScale(sf::Vector2f(4, 4));

	if (!m_exitButtonTexture.loadFromFile("ASSETS\\IMAGES\\exit.png"))
	{
		std::cout << "Problem loading play button texture" << std::endl;
	}
	m_exitButtonSprite.setTexture(m_exitButtonTexture);
	m_exitButtonSprite.setPosition(455.0f, 350.0f);
	m_exitButtonSprite.setScale(sf::Vector2f(4, 4));

	if (!backgroundTexture.loadFromFile("ASSETS\\IMAGES\\background.gif"))
	{
		std::cout << "Problem loading play button texture" << std::endl;
	}
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(static_cast<float>(SCREEN_WIDTH) / backgroundSprite.getLocalBounds().width,
		static_cast<float>(SCREEN_HEIGHT) / backgroundSprite.getLocalBounds().height);

	if (!m_tileTexture.loadFromFile("ASSETS\\IMAGES\\tile.png"))
	{
		std::cout << "Problem loading play button texture" << std::endl;
	}
	m_tileSprite.setTexture(m_tileTexture);
	m_tileSprite.setPosition(435.0f, 130.0f);
	m_tileSprite.setScale(sf::Vector2f(3, 3));
}

void Game::restartGame()
{
	m_gameState = GameState::MainMenu;
	m_exitGame = false;
	m_enemySpeed = 1.5f;

	initialize();
}

void Game::initialize()
{
	m_window.create(sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "SFML Game");
	m_gameState = GameState::MainMenu;
	m_exitGame = false;
	m_pickup = Pickup(pickupTexture);
	fog.candle::LightingArea::FOG, sf::Vector2f(-SCREEN_HEIGHT, -SCREEN_WIDTH), sf::Vector2f(SCREEN_WIDTH * 5, SCREEN_HEIGHT * 5);
	fog.setAreaColor(sf::Color::Black);
	light.setRange(600);
	light.setIntensity(0.5);
	light.setColor(sf::Color(255, 140, 0, 150));

	loadTextures();
	setupFontAndText();
	setupSprite();
	loadAudio();
	spawnEnemy();

	std::vector<Rectangle> buildings;
	buildings.push_back(rect1);
	buildings.push_back(Rectangle{ x1, y1, width1, height1 });
	setupFontAndText();
	setupSprite();

}

void Game::spawnEnemy() {
	m_enemy.init(m_enemyTexture, sf::Vector2f(200.0f, 700.0f)); 
}


void Game::loadAudio()
{
	if (!m_backgroundMusic.openFromFile("ASSETS\\AUDIO\\oblivian.ogg"))
	{
		std::cout << "Error loading background music." << std::endl;
	}
	m_backgroundMusic.play();
	m_backgroundMusic.setLoop(true);


}
