#include "PlayerHeart.h"

// Private Functions.
void PlayerHeart::InitText()
{
	if (!_heart_texture.loadFromFile("Textures/Heart.png"))
		std::cout << "Cannot load Heart.png onto PlayerHeart::InitText()" << std::endl;
	else
		std::cout << "Loaded Heart.png onto PlayerHeart::InitText()" << std::endl;
}

void PlayerHeart::InitSprite()
{
	_heart_sprite.setTexture(this->_heart_texture);

	_heart_sprite.scale(2.f, 2.f);								// Rescale the heart sprite.
	std::cout << "Bound texture to sprite in PlayerHeart::InitSprite() function" << std::endl;

	this->_rect_source_sprite = sf::IntRect(0, 0, 18, 14);		// x, y, w, h
	_heart_sprite.setTextureRect(_rect_source_sprite);			// First heart on the sprite sheet coord (17, 14)

}

// Const
PlayerHeart::PlayerHeart()
{
	InitText();
	InitSprite();
	
	_heart_sprite.setPosition(50.f, 60.f);			// Permanent position for the heart for player. This position is for heart 1.
	
	// Sets up Animation Parameters value
	_num_frames = 8;						// Frames in sprite sheet 
	_frame_duration = 100;					// Duration of each frame in miliseconds.
	_current_frame = 0;	

	_ptr_curr_frame = &_current_frame;
}
// Destructor
PlayerHeart::~PlayerHeart()
{
}

// Functions.
sf::Sprite PlayerHeart::GetHeartSprite()
{
	return _heart_sprite;
}

void PlayerHeart::Animation()
{
	// Animates the heart sprite. Loops through all 8 frames in 200 miliseconds.
	if (_clock.getElapsedTime().asMilliseconds() >= 200.f)
	{
		// Advance to next frame.
		_current_frame = (_current_frame + 1) % _num_frames;

		// Update texture rectangle.
		_rect_source_sprite.left = _current_frame * 18;
		// std::cout << "Rect. Left : " << _rect_source_sprite.left << std::endl;
		_heart_sprite.setTextureRect(_rect_source_sprite);

		_clock.restart();
	}
}

// Draw heart itself.
void PlayerHeart::Render(sf::RenderWindow& target)
{
	target.draw(_heart_sprite);
}

// sets the positions for the heart. Only changing the x position as the y position will be fixed.
void PlayerHeart::HeartSetPosition(double x)
{
	_heart_sprite.setPosition(x, 60);
}
