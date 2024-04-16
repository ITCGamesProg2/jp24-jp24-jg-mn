/// @author Monika Nusi and katrina Gorska
/// @date 09/04/2024


#include "Game.h"
#include "ai_enemy.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{ false }, 
	m_frameDuration(0.2f),
	m_currentFrame(0),
	m_gameState(GameState::MainMenu),
	m_playerCharacter(PlayerCharacter::None),
	m_shootCooldown(sf::seconds(0.3f)),
	m_pickup(pickupTexture)
{
	setupFontAndText(); 
	setupSprite(); 

	std::vector<Rectangle> buildings;
	buildings.push_back(rect1);
	buildings.push_back(Rectangle{ x1, y1, width1, height1 }); 
	setupFontAndText(); // load font 
	setupSprite(); // load texture

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



	if (m_gameState == GameState::Playing && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		shoot();
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

void Game::handleMainMenuClick(const sf::Vector2f& mousePosition)
{
	if (m_exitButtonSprite.getGlobalBounds().contains(mousePosition))
	{
		std::cout << "Exiting Game!" << std::endl;
		m_exitGame = true;
	}
	else if (m_crabSprite.getGlobalBounds().contains(mousePosition))
	{
		selectCharacter(PlayerCharacter::Crab);
	}
	else if (m_foxSprite.getGlobalBounds().contains(mousePosition))
	{
		selectCharacter(PlayerCharacter::Fox);
	}
	else if (m_goatSprite.getGlobalBounds().contains(mousePosition))
	{
		selectCharacter(PlayerCharacter::Goat);
	}
	else if (m_playButtonSprite.getGlobalBounds().contains(mousePosition))
	{
		if (m_playerCharacter != PlayerCharacter::None)
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

void Game::selectCharacter(PlayerCharacter character)
{
	m_playerCharacter = character;
	std::cout << "Selected ";
	switch (character)
	{
	case PlayerCharacter::Crab:
		std::cout << "Crab";
		break;
	case PlayerCharacter::Fox:
		std::cout << "Fox";
		break;
	case PlayerCharacter::Goat:
		std::cout << "Goat";
		break;
	default:
		std::cout << "None";
		break;
	}
	std::cout << "!" << std::endl;
}

void Game::startPlaying()
{
	m_gameState = GameState::Playing;
	std::cout << "Starting Game!" << std::endl;
}


void Game::shoot()
{
	if(m_shootTimer.getElapsedTime() >= m_shootCooldown)
	{
		sf::Vector2f playerCenter = m_crabSprite.getPosition(); 
		sf::Vector2f aimDirection = sf::Vector2f(1.f, 0.f); 

		
		sf::Texture& projectileTexture = (m_playerCharacter == PlayerCharacter::Crab) ? m_crabProjectileTexture :
			(m_playerCharacter == PlayerCharacter::Fox) ? m_foxProjectileTexture :
			(m_playerCharacter == PlayerCharacter::Goat) ? m_goatProjectileTexture:
			m_crabTexture;

		Projectile projectile(playerCenter, std::atan2(aimDirection.y, aimDirection.x), projectileTexture);
		m_projectiles.push_back(projectile);

		m_shootTimer.restart();
	}
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

	float movementSpeed = 2.0f;
	if (m_pickup.isActive()) {
		movementSpeed = 4.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_playerPosition.y -= movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_playerPosition.y += movementSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_playerPosition.x -= movementSpeed;
		m_playerDirection = Direction::Left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_playerPosition.x += movementSpeed;
		m_playerDirection = Direction::Right;
	}

	m_crabSprite.setPosition(m_playerPosition);
	m_foxSprite.setPosition(m_playerPosition);
	m_goatSprite.setPosition(m_playerPosition);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

		for (int i = 0; i < 5; ++i) {
			sf::Vector2f randomOffset = sf::Vector2f((rand() % 10) - 5, (rand() % 10) - 5);
			sf::Vector2f particlePosition = m_playerPosition + sf::Vector2f(0.0f, 40.0f) + randomOffset;
			sf::Vector2f randomVelocity = sf::Vector2f((rand() % 100) - 50, (rand() % 100) - 50);
			sf::Color particleColor = sf::Color::Black;
			float lifetime = 0.2;
			Particle particle(particlePosition, randomVelocity, particleColor, lifetime);
			m_particles.push_back(particle);
		}
	}
	updateParticles(t_deltaTime);

	updateAnimation();

	for (auto it = m_projectiles.begin(); it != m_projectiles.end(); )
	{
		it->update(t_deltaTime);

		if (it->getPosition().x < 0 || it->getPosition().x > m_window.getSize().x ||
			it->getPosition().y < 0 || it->getPosition().y > m_window.getSize().y)
		{
			it = m_projectiles.erase(it);
		}
		else
		{
			++it;
		}
	}
	if (m_gameState == GameState::Playing)
	{

		if (m_pickup.isCollected(m_crabSprite.getGlobalBounds()))
		{
			m_pickup.applyEffect(m_crabSprite); 
			m_pickup.spawn(sf::Vector2f(rand() % 700 + 50, rand() % 500 + 50)); 
		}
		else if (m_pickup.isCollected(m_foxSprite.getGlobalBounds()))
		{
			m_pickup.applyEffect(m_foxSprite);
			m_pickup.spawn(sf::Vector2f(rand() % 700 + 50, rand() % 500 + 50));
		}
		else if (m_pickup.isCollected(m_goatSprite.getGlobalBounds()))
		{
			m_pickup.applyEffect(m_goatSprite);
			m_pickup.spawn(sf::Vector2f(rand() % 700 + 50, rand() % 500 + 50));
		}

		updatePlayerSpriteColor(m_crabSprite);
		updatePlayerSpriteColor(m_foxSprite);
		updatePlayerSpriteColor(m_goatSprite);
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
	}
}

void Game::drawParticles() {
	for (const auto& particle : m_particles) {
		particle.draw(m_window);
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
			particlePosition.y += 25.0f;
			sf::Vector2f randomVelocity = sf::Vector2f((rand() % 100) - 50, (rand() % 100) - 50);
			sf::Color particleColor = sf::Color::Black;
			float lifetime = 0.2;
			Particle particle(particlePosition, randomVelocity, particleColor, lifetime);
			m_particles.push_back(particle);
		}
	}
}


void Game::updateAnimation()
{
	if (m_animationClock.getElapsedTime().asSeconds() >= m_frameDuration)
	{
		m_animationClock.restart();


		m_currentFrame = (m_currentFrame + 1) % 4;

		int frameWidth = 16;
		int frameHeight = 16;
		int framesPerRow = 4;
		int frameX = (m_currentFrame % framesPerRow) * frameWidth;
		int frameY = (m_currentFrame / framesPerRow) * frameHeight;

		sf::IntRect frameRect(frameX, frameY, frameWidth, frameHeight);
		m_crabSprite.setTextureRect(frameRect);
		m_foxSprite.setTextureRect(frameRect);
		m_goatSprite.setTextureRect(frameRect);
	}
}

bool Game::checkCollision(float objX, float objY, float objWidth, float objHeight, const Rectangle& rect) {
	return (objX < rect.x + rect.width && objX + objWidth > rect.x &&
		objY < rect.y + rect.height && objY + objHeight > rect.y);
}

bool Game::checkCollisions(float objX, float objY, float objWidth, float objHeight, const std::vector<Rectangle>& rectangles) {
	for (const auto& rect : rectangles) {
		if (checkCollision(objX, objY, objWidth, objHeight, rect)) {
			
			return true;
		}
	}
	
	return false;
}

void Game::render()
{
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
		selectedCharacterText.setFillColor(sf::Color::Black);

		if (m_playerCharacter == PlayerCharacter::Crab)
		{
			selectedCharacterText.setString("Selected Character: Crab");
		}
		else if (m_playerCharacter == PlayerCharacter::Fox)
		{
			selectedCharacterText.setString("Selected Character: Fox");
		}
		else if (m_playerCharacter == PlayerCharacter::Goat)
		{
			selectedCharacterText.setString("Selected Character: Goat");
		}
		else
		{
			selectedCharacterText.setString("Selected Character:");
		}

		selectedCharacterText.setPosition(300.0f, 230.0f);
		m_window.draw(selectedCharacterText);
	}
	else if (m_gameState == GameState::Playing)
	{
		m_window.draw(gameBackgroundSprite);

		drawParticles();

		if (m_playerCharacter == PlayerCharacter::Crab)
		{
			m_crabSprite.setPosition(m_playerPosition);
			m_crabSprite.setScale((m_playerDirection == Direction::Left) ?
				sf::Vector2f(-3.0f, 3.0f) : sf::Vector2f(3.0f, 3.0f));
			m_window.draw(m_crabSprite);
		}
		else if (m_playerCharacter == PlayerCharacter::Fox)
		{
			m_foxSprite.setPosition(m_playerPosition);
			m_foxSprite.setScale((m_playerDirection == Direction::Left) ?
				sf::Vector2f(-3.0f, 3.0f) : sf::Vector2f(3.0f, 3.0f));
			m_window.draw(m_foxSprite);
		}
		else if (m_playerCharacter == PlayerCharacter::Goat)
		{
			m_goatSprite.setPosition(m_playerPosition);
			m_goatSprite.setScale((m_playerDirection == Direction::Left) ?
				sf::Vector2f(-3.0f, 3.0f) : sf::Vector2f(3.0f, 3.0f));
			m_window.draw(m_goatSprite);
		}
		m_pickup.draw(m_window);

		m_window.draw(m_pauseButtonSprite);
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

	for (const auto& projectile : m_projectiles)
	{
		projectile.draw(m_window);
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
	title.setPosition(200.0f, 40.0f);
	title.setCharacterSize(100U);
	title.setFillColor(sf::Color::Black);

}


void Game::setupSprite()
{

	if (!m_crabTexture.loadFromFile("ASSETS\\IMAGES\\crabSpritesheet.png"))
	{
		std::cout << "Problem loading spritesheet" << std::endl;
		return;
	}
	sf::IntRect initialFrameRect(0, 0, 16, 16);

	m_crabSprite.setTexture(m_crabTexture);
	m_crabSprite.setTextureRect(initialFrameRect);
	m_crabSprite.setPosition(290.0f, 165.0f);
	m_crabSprite.setScale(3.0f, 3.0f);

	if (!m_foxTexture.loadFromFile("ASSETS\\IMAGES\\foxSpritesheet.png"))
	{
		std::cout << "Problem loading spritesheet" << std::endl;
		return;
	}
	sf::IntRect foxFrameRect(0, 0, 16, 16);

	m_foxSprite.setTexture(m_foxTexture);
	m_foxSprite.setTextureRect(foxFrameRect);
	m_foxSprite.setPosition(360.0f, 165.0f);
	m_foxSprite.setScale(3.0f, 3.0f);

	if (!m_goatTexture.loadFromFile("ASSETS\\IMAGES\\goatSpritesheet.png"))
	{
		std::cout << "Problem loading spritesheet" << std::endl;
		return;
	}
	sf::IntRect goatFrameRect(0, 0, 16, 16);

	m_goatSprite.setTexture(m_goatTexture);
	m_goatSprite.setTextureRect(goatFrameRect);
	m_goatSprite.setPosition(440.0f, 165.0f);
	m_goatSprite.setScale(3.0f, 3.0f);

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
	m_pickup = Pickup(pickupTexture);
	sf::Vector2f randomPosition = sf::Vector2f(rand() % 700 + 50, rand() % 500 + 50);
	m_pickup.spawn(randomPosition);

	if (!m_pauseButtonTexture.loadFromFile("ASSETS\\IMAGES\\pause.png"))
	{
		std::cout << "Problem loading pause button texture" << std::endl;
	}
	m_pauseButtonSprite.setTexture(m_pauseButtonTexture);
	m_pauseButtonSprite.setPosition(720.0f, 10.0f);
	m_pauseButtonSprite.setScale(sf::Vector2f(2, 2));
	
	if (!m_playButtonTexture.loadFromFile("ASSETS\\IMAGES\\play.png"))
	{
		std::cout << "Problem loading play button texture" << std::endl;
	}
	m_playButtonSprite.setTexture(m_playButtonTexture);
	m_playButtonSprite.setPosition(200.0f, 250.0f);
	m_playButtonSprite.setScale(sf::Vector2f(4, 4));

	if (!m_exitButtonTexture.loadFromFile("ASSETS\\IMAGES\\exit.png"))
	{
		std::cout << "Problem loading play button texture" << std::endl;
	}
	m_exitButtonSprite.setTexture(m_exitButtonTexture);
	m_exitButtonSprite.setPosition(255.0f, 350.0f);
	m_exitButtonSprite.setScale(sf::Vector2f(4, 4));

	if (!backgroundTexture.loadFromFile("ASSETS\\IMAGES\\background.jpg"))
	{
		std::cout << "Problem loading play button texture" << std::endl;
	}
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(sf::Vector2f(1.7, 2.30));

	if (!gameBackgroundTexture.loadFromFile("ASSETS\\IMAGES\\gameBackground.jpg"))
	{
		std::cout << "Problem loading play button texture" << std::endl;	
	}
	gameBackgroundSprite.setTexture(gameBackgroundTexture);
	gameBackgroundSprite.setScale(sf::Vector2f(1.2, 1.2));

	if (!m_tileTexture.loadFromFile("ASSETS\\IMAGES\\tile.png"))
	{
		std::cout << "Problem loading play button texture" << std::endl;
	}
	m_tileSprite.setTexture(m_tileTexture);
	m_tileSprite.setPosition(235.0f, 130.0f);
	m_tileSprite.setScale(sf::Vector2f(3, 3));
}
