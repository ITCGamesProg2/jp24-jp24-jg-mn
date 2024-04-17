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
		m_playerDirection = Direction::Up;
		isMoving = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_playerPosition.y += movementSpeed;
		m_playerDirection = Direction::Down;
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

sf::Vector2f Player::getAimDirection() const
{
	sf::Vector2f aimDirection;

	switch (m_playerDirection)
	{
	case Direction::Left:
		return sf::Vector2f(-1.f, 0.f);
	case Direction::Right:
		return sf::Vector2f(1.f, 0.f);
	case Direction::Up:
		return sf::Vector2f(0.f, -1.f);
	case Direction::Down:
		return sf::Vector2f(0.f, 1.f);
	default:
		return sf::Vector2f(0.f, 0.f);
	}
	return aimDirection;

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

	sf::Vector2f aimDirection = getAimDirection();

	// Pass aiming direction to the weapon when shooting
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		m_weapon.shoot(m_playerSprite.getPosition(), aimDirection);
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



