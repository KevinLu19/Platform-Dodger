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
}

// Const
Animation::Animation(std::string texture_file_location, int frames, int sprite_height) : _sprite_height(sprite_height)
{
	InitText(texture_file_location);
	InitSprite();

	_num_frames = frames;
	_current_frame = 0;
}

// Dest
Animation::~Animation()
{
}

// Functions
sf::Sprite Animation::AnimateSpriteSheetSeconds()
{
	if (_clock.getElapsedTime().asSeconds() > 1.0f)
	{
		_current_frame = (_current_frame + 1) % _num_frames;

		// Update the rectangle on sf::IntRect
		_sprite_rect.left = _current_frame * _sprite_height;

		_sprite.setTextureRect(_sprite_rect);

		_clock.restart();
	}

	return _sprite;
}