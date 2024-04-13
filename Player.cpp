#include "Player.h"

// Private Functions
void Player::initTexture()
{
	// Load a texutre from file.
	if (!this->_texture.loadFromFile("Textures/chocobo.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture from file." << std::endl;
	}
}

void Player::initSprite()
{
	// Set the texture to the sprite.
	this->_sprite.setTexture(this->_texture);

	// Resize sprite.
	this->_sprite.scale(0.75f, 0.75f);

	_sprite.setPosition(600.f, 300.f);
}

// Conv / Des
Player::Player()
{
	this->initTexture();
	this->initSprite();
	_movement_speed = 2.f;
	
	_player_heart = new PlayerHeart();
}

Player::~Player()
{
	delete _player_heart;
}

// Functions
void Player::Update()
{

}

void Player::Render(sf::RenderTarget& target)
{
	target.draw(this->_sprite);
}

void Player::Move(const float dir_x, const float dir_y)
{
	this->_sprite.move(this->_movement_speed * dir_x, this->_movement_speed * dir_y);
}

sf::Sprite Player::GetSprite()
{
	return _sprite;
}
