#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

// Class for objects that player can interact with such as statues or chests.
class InteractiveObject
{
private:
	sf::Texture _texture;
	sf::Sprite _sprite;

	sf::IntRect _rect_sprite;

	void InitText();
	void InitSprite();

public:
	InteractiveObject(int pos_x, int pos_y);
	InteractiveObject();
	~InteractiveObject();

	void Render(sf::RenderTarget& target);
	void SetPosition(int pos_x, int pos_y);

	sf::Sprite GetSprite();
};

