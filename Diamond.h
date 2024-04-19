#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"

class Diamond
{
private:
	sf::Sprite _diamond_sprite;
	sf::Texture _diamond_text;

	Animation * _animation;					// Diamond has-a relationship to Animation.
	
	sf::IntRect _rect_source_sprite;

	sf::Vector2i _position;
	sf::Clock _clock;

	int _num_frames, _frame_duration, _current_frame, _frame_width;

	// Private functions
	void InitText();
	void InitSprite();


public:
	Diamond();
	~Diamond();

	// Functions
	void DiamondAnimate();
	void Render(sf::RenderTarget & target);
};

