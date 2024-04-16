#include "player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::init(sf::Texture& t_textures, sf::Texture& t_bulletTexture)
{
	m_weapon.init(t_bulletTexture);
	m_playerSprite.setTexture(t_textures);
	m_playerSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	m_playerSprite.setOrigin(8, 8);
	m_playerSprite.setScale(3.0f, 3.0f);
}

void Player::move()
{

	float movementSpeed = 2.0f;
	/*if (m_pickup.isActive()) {
		movementSpeed = 4.0f;
	}*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_playerPosition.y -= movementSpeed;
		isMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_playerPosition.y += movementSpeed;
		isMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_playerPosition.x -= movementSpeed;
		m_playerDirection = Direction::Left;
		isMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_playerPosition.x += movementSpeed;
		m_playerDirection = Direction::Right;
		isMoving = true;
	}

	m_playerSprite.setPosition(m_playerPosition);
}

void Player::changeDirection()
{
	m_playerSprite.setScale((m_playerDirection == Direction::Left) ?
		sf::Vector2f(-3.0f, 3.0f) : sf::Vector2f(3.0f, 3.0f));
}

void Player::update(sf::Time t_deltaTime)
{
	move();
	changeDirection();
	animate();
	m_weapon.update(t_deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		m_weapon.shoot(m_playerSprite.getPosition());
	}
}

void Player::render(sf::RenderWindow& m_window)
{
	m_window.draw(m_playerSprite);
	m_weapon.render(m_window);
}

void Player::animate()
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
		m_playerSprite.setTextureRect(frameRect);
	}
}

void Player::updatePlayerSpriteColour(bool pickUpActive)
{
	if (pickUpActive)
	{
		m_playerSprite.setColor(sf::Color::Red);
	}
	else
	{
		m_playerSprite.setColor(sf::Color::White);
	}
}

void Player::selectCharacter(PlayerCharacter t_playerCharacter)
{
    m_playerCharacter = t_playerCharacter;
}



