#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class PlayerHeart
{
private:
	sf::Sprite _heart_sprite;
	sf::Texture _heart_texture;

	int _num_hearts;

	void InitText();
	void InitSprite();

public:
	PlayerHeart();
	~PlayerHeart();
	
	sf::Sprite GetHeartSprite();

	void Animation();
};

