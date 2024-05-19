#include "Player.h"

// Private Functions
void Player::initTexture()
{
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
	_movement_speed = 600.0f;					// Movespeed for the game.

	_current_frame = 0;	
	_frame_width = _powerup.getSize().x / 10;

	_sprite.setPosition(600.f, 300.f);			// Initial position for player sprite.
	delta_time = _clock.restart().asSeconds();	// Clock used for movement per second. Clock runs per second.

	_gravity = 100.0f;							// Gravity strength.
	_jump_velocity = 0.0f;
	_is_jumping = false;

	_heart_taken = false;						// Used for TakeDamage()

	
}

Player::~Player()
{

}

// Functions
void Player::Update()
{
	sf::Vector2f movement(0.0f, 0.0f);				// Handles player movement.

	// Handles movement for the player class along with sprite switching from direction.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		// Want dashing to have a special animation. 
		// Where when button is held down, animation will just be frame 3 and 4 and repeat that until button is released.

		_sprite.setTexture(_dash_left);
		GetFrameWidth(_dash_left, 4);
		// Animate(4);

		AnimateDash();

		//Move(-1.f, 0.f);
		movement.x -= _movement_speed * delta_time;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		// Want dashing to have a special animation. 
		// Where when button is held down, animation will just be frame 3 and 4 and repeat that until button is released.

		_sprite.setTexture(_dash_right);
		GetFrameWidth(_dash_right, 4);
		//Animate(4);

		AnimateDash();

		//Move(1.f, 0.f);
		movement.x += _movement_speed * delta_time;
	}
	
	// Disable W button because want to use w on special occasions such as "climbing ladder, power up on statues, etc"
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//{
	//	_sprite.setTexture(_jump);
	//	GetFrameWidth(_jump, 6);
	//	Animate(6);

	//	// Need to implement jump without holding down button.
	//	//Move(0.f, -3.f);

	//	movement.y -= _movement_speed * delta_time;
	//}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_sprite.setTexture(_falling);
		GetFrameWidth(_falling, 3);
		Animate(3);

		// Need to implement falling with gravity.

		//Move(0.f, 3.f);
		movement.y += _movement_speed * delta_time;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))			// Handles jump.
	{
		_sprite.setTexture(_jump);
		Animate(6);

		_is_jumping = true;
		_jump_velocity = -1500.0f;										// Iniital jump velocity.

		// Apply Gravity if jumping
		if (_is_jumping)
		{
			_jump_velocity += _gravity * delta_time;
			movement.y += _jump_velocity * delta_time;

			// Check if sprite landed.
			if (_sprite.getPosition().y >= 500)
			{
				_is_jumping = false;
				_jump_velocity = 0.0f;

				_sprite.setPosition(_sprite.getPosition().x, 500);		// Set player on the ground
			}
		}
	}
	else
	{
		// Standing / Default sprite animation will be idle when no input in given.
		_sprite.setTexture(_idle);
		GetFrameWidth(_idle, 4);
		Animate(4);
	}
	
	

	// Move the sprite
	_sprite.move(movement);

}

void Player::Render(sf::RenderTarget& target)
{
	target.draw(this->_sprite);
}

// Move given player sprite using _movement_speed variable.
void Player::Move(float dir_x, float dir_y)
{
	_sprite.move(_velocity_x + dir_x, _velocity_y + dir_y);
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
		//std::cout << "Inside Player::Aniamte() Function in Player.cpp file" << std::endl;

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
		
		// Frame count 4.
		if (_current_frame == 3)
		{
			//std::cout << "Currently in frame 4" << std::endl;
			_current_frame = 2;			// Switch to frame 3. 2 is the idnex for frame 3.

			_sprite.setTextureRect(frame_3_rect);

			//std::cout << "Current frame = 4. Switching to frame 3." << std::endl;
		}

		_clock.restart();
	}
}

// Animates the hurt sprite.
void Player::AnimateHurt()
{
	_sprite.setTexture(_hurt);


	if (_clock.getElapsedTime().asMilliseconds() > 100.f)
	{
		_current_frame = (_current_frame + 1) % 4;

		// Update texture rectangle.
		_rect_sprite.left = _current_frame * _frame_width;

		_sprite.setTextureRect(_rect_sprite);

		_clock.restart();
;	}
}

void Player::TakeDamage(int & health, std::vector<PlayerHeart> & _hearts)
{
	if (health > 0 && _heart_taken == false)
	{
		_hearts.pop_back();		// Pops out one of the heart.

		health--;				// Reduces health by 1.

		_heart_taken = true;	// After reduced heart by 1, flag heart taken to be true.
	}
}