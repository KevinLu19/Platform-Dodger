#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Animation
{
private:
	
	sf::Clock _clock;						// Animation timing.

	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::IntRect _sprite_rect;				// x, y, w, h

	int _num_frames, _current_frame;

	// Variables used for initial sprite bindning.
	int _frame_width, _frame_height;

	// Setting up the texture and sprite.
	void InitText(std::string texture_file_location);				// Gets the Texture for sprite.
	void InitSprite();
public:
	Animation(std::string texture_file_location, int frames, int frame_width, int frame_height);
	~Animation();

	// Functions
	sf::Sprite AnimateSpriteSheetSeconds();
};

