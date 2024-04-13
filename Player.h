#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "PlayerHeart.h"

class Player
{
private:
	sf::Sprite _sprite;
	sf::Texture _texture;

	float _movement_speed;

	sf::FloatRect _player_bounding_box = _sprite.getGlobalBounds();

	PlayerHeart * _player_heart;

	// Private Functions
	void initTexture();
	void initSprite();

public:
	Player();
	~Player();

	//Functions
	void Update();
	void Render(sf::RenderTarget& target);
	void Move(const float dir_x, const float dir_y);
	sf::Sprite GetSprite();
};

