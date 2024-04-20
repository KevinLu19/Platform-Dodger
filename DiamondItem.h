#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"


class DiamondItem
{
private:
	int _num_frames, _current_frame, _frame_width;

	sf::Texture _texture;
	sf::Sprite _sprite;

	Animation * _animation;

public:
	DiamondItem();
	~DiamondItem();

	void Animate();
	void Render(sf::RenderTarget & target);
};

