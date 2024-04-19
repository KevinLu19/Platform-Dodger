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

	int _num_frames, _current_frame, _sprite_height;

	void InitText(std::string texture_file_location);
	void InitSprite();
public:
	Animation(std::string texture_file_location, int frames, int sprite_height);
	~Animation();

	// Functions
	sf::Sprite AnimateSpriteSheetSeconds();
};

