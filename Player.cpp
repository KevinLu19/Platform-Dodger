#include "Player.h"

// Private Functions
void Player::initTexture()
{
	//// Load a texutre from file.
	//if (!this->_texture.loadFromFile("Textures/chocobo.png"))
	//{
	//	std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture from file." << std::endl;
	//}

	// Loading all the sprite textures.
	if (!_powerup.loadFromFile("Textures/PowerUp.png"))
		std::cout << "Cannot load PowerUp Sprite Texture" << std::endl;
	if (!_idle.loadFromFile("Textures/Idle.png"))
		std::cout << "Cannot load Idle Sprite Texture" << std::endl;
	if (!_jump.loadFromFile("Textures/Jump.png"))
		std::cout << "Cannot load Jump Sprite Texture" << std::endl;
	if (!_landing.loadFromFile("Textures/Landing.png"))
		std::cout << "Cannot load Landing Sprite Texture" << std::endl;
	if (!_dash_right.loadFromFile("Textures/Dashing.png"))
		std::cout << "Cannot load Dashing Sprite Texture" << std::endl;
	if (!_dash_left.loadFromFile("Textures/Left_Dash.png"))
		std::cout << "Cannot load Left dashing Sprite Texture" << std::endl;
	if (!_falling.loadFromFile("Textures/Falling.png"))
		std::cout << "Cannot load Falling Sprite Texture" << std::endl;
	if (!_hurt.loadFromFile("Textures/Hurt.png"))
		std::cout << "Cannot load Hurt Sprite Texture" << std::endl;
}

void Player::initSprite()
{
	// Set initial texture to be idle position.
	_sprite.setTexture(_powerup);

	// Resize sprite.
	_sprite.scale(1.2f, 1.2f);

	// Set initial sprite Rectangle.		idle = 50 x 63
	_rect_sprite = sf::IntRect(0, 0, 65, 63);			// x, y, w, h

	_sprite.setTextureRect(_rect_sprite);
}

// Conv / Des
Player::Player()
{
	this->initTexture();
	this->initSprite();
	_movement_speed = 2.f;

	_current_frame = 0;
	_num_frames = 10;			// Test using Power Up sprite.
	_frame_width = _powerup.getSize().x / 10;

	_sprite.setPosition(600.f, 300.f);			// Initial position for player sprite.

	// _player_heart = new PlayerHeart();
}

Player::~Player()
{
	// delete _player_heart;
}

// Functions
void Player::Update()
{
	// Handles movement for the player class along with sprite switching from direction.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_sprite.setTexture(_dash_left);
		GetFrameWidth(_dash_left, 4);
		Animate(4);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_sprite.setTexture(_dash_right);
		GetFrameWidth(_dash_right, 4);
		Animate(4);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_sprite.setTexture(_jump);
		GetFrameWidth(_jump, 6);
		Animate(6);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_sprite.setTexture(_falling);
		GetFrameWidth(_falling, 3);
		Animate(3);
	}
	else
	{
		// Standing / Default sprite animation will be idle when no input in given.
		_sprite.setTexture(_idle);
		GetFrameWidth(_idle, 4);
		Animate(4);
	}
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

// Handles the frame width of different sprite.
int Player::GetFrameWidth(sf::Texture & texture, int frames)
{
	_frame_width = texture.getSize().x / frames;

	return _frame_width;
}


// Animate Player Sprite
void Player::Animate(int num_frames)
{
	if (_clock.getElapsedTime().asMilliseconds() >= 200.f)
	{
		//std::cout << "Inside if statement " << std::endl;
		// Advance to next frame.
		_current_frame = (_current_frame + 1) % num_frames;

		// Update texture rectangle.
		_rect_sprite.left = _current_frame * _frame_width;
		// std::cout << "Rect. Left : " << _rect_source_sprite.left << std::endl;
		_sprite.setTextureRect(_rect_sprite);

		_clock.restart();
	}
}
