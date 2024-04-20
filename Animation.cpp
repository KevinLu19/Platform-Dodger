#include "Animation.h"

// Private Function
void Animation::InitText(std::string texture_file_location)
{
	if (!_texture.loadFromFile(texture_file_location))
	{
		std::cout << "Cannot load " << texture_file_location << " in Animation::InitText" << std::endl;
	}
}

void Animation::InitSprite()
{
	_sprite.setTexture(this->_texture);
	this->_sprite_rect = sf::IntRect(0,0, _frame_width, _frame_height);
}

// Const
Animation::Animation(std::string texture_file_location, int frames, int frame_width, int frame_height)
		: _frame_width(frame_width)
		, _frame_height(frame_height)
		, _num_frames(frames)
{
	InitText(texture_file_location);
	InitSprite();

	_current_frame = 0;
}

// Dest
Animation::~Animation()
{
}

// Functions
sf::Sprite Animation::AnimateSpriteSheetSeconds()
{
	if (_clock.getElapsedTime().asSeconds() > .30f)
	{
		_current_frame = (_current_frame + 1) % _num_frames;

		// Update the rectangle on sf::IntRect
		_sprite_rect.left = _current_frame * _frame_width;
		_sprite.setTextureRect(_sprite_rect);

		_clock.restart();
	}

	return _sprite;
}