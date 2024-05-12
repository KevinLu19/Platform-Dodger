#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Platform
{
private:
	sf::Texture _platform_text;
	sf::Sprite _platform_sprite;

	sf::IntRect _platform_rect;

	void InitText();
	void InitSprite();

public:
	Platform(sf::Vector2f position);
	~Platform();

	void Render(sf::RenderWindow & target);
};

