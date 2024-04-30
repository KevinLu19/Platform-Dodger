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

	// Set initial sprite Rectangle.					idle = 50 x 63
	_rect_sprite = sf::IntRect(0, 0, 65, 63);			// x, y, w, h

	_sprite.setTextureRect(_rect_sprite);
}

// Conv / Des
Player::Player()
{
	this->initTexture();
	this->initSprite();
	_movement_speed = 2.5f;

	_current_frame = 0;
	_num_frames = 10;			// Test using Power Up sprite.
	_frame_width = _powerup.getSize().x / 10;

	_sprite.setPosition(600.f, 300.f);			// Initial position for player sprite.
}

Player::~Player()
{
}

// Functions
void Player::Update()
{
	// Handles movement for the player class along with sprite switching from direction.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		// Want dashing to have a special animation. 
		// Where when button is held down, animation will just be frame 3 and 4 and repeat that until button is released.

		_sprite.setTexture(_dash_left);
		GetFrameWidth(_dash_left, 4);
		// Animate(4);

		AnimateDash();

		Move(-1.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// Want dashing to have a special animation. 
		// Where when button is held down, animation will just be frame 3 and 4 and repeat that until button is released.

		_sprite.setTexture(_dash_right);
		GetFrameWidth(_dash_right, 4);
		//Animate(4);

		AnimateDash();

		Move(1.f, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_sprite.setTexture(_jump);
		GetFrameWidth(_jump, 6);
		Animate(6);

		// Need to implement jump without holding down button.
		Move(0.f, - 3.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_sprite.setTexture(_falling);
		GetFrameWidth(_falling, 3);
		Animate(3);

		// Need to implement falling with gravity.

		Move(0.f, 3.f);
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

// Move given player sprite using _movement_speed variable.
void Player::Move(float dir_x, float dir_y)
{
	_sprite.move(_velocity_x * dir_x, _velocity_y * dir_y);
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


// Animate Player Sprite(s)
void Player::Animate(int num_frames)
{
	if (_clock.getElapsedTime().asMilliseconds() >= 170.f)
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

// Handles the dash left and right sprite. 
// When A or D is pressed, as long as the button is held down, want to only cycle between frame 3 and 4. 
void Player::AnimateDash()
{
	// Dashing left or right animation frame 3 and 4 setup.
	frame_3_rect = sf::IntRect(2 * _frame_width, 0, _frame_width, 63);
	frame_4_rect = sf::IntRect(3 * _frame_width, 0, _frame_width, 63);

	// Will run every 100 milisecond.
	if (_clock.getElapsedTime().asMilliseconds() >= 100.f)
	{
		_current_frame = (_current_frame + 1) % 4;

		//// Frame count 3.
		//if (_current_frame == 2)
		//{
		//	_current_frame = 3;			// Switch to frame 4. 3 is the index for frame 4.
		//	_sprite.setTextureRect(frame_4_rect);

		//	std::cout << "Current frame = 3. Switching to frame 4." << std::endl;
		//}

		
		// Frame count 4.
		if (_current_frame == 3)
		{
			std::cout << "Currently in frame 4" << std::endl;
			_current_frame = 2;			// Switch to frame 3. 2 is the idnex for frame 3.

			_sprite.setTextureRect(frame_3_rect);

			std::cout << "Current frame = 4. Switching to frame 3." << std::endl;
		}

		_clock.restart();
	}
}


// Fixed Height Jump
// ** Important: need to make sure character is on the ground before initiate a jump.
void Player::OnJumpKeyPressed()
{
	_velocity_y = -5.f;			// Gives a vertical boost to the players velocity to start.
}

// Variabled Height Jumps
void Player::OnJumpKeyReleased()
{
	if (_velocity_y < -6.0f)			// If character still ascending in the jump
		_velocity_y = -6.0f;			// Limit the speed of ascent.
}