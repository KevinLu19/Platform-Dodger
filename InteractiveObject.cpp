#include "InteractiveObject.h"

void InteractiveObject::InitText()
{
	if (!_texture.loadFromFile("Textures/Statue.png"))
	{
		std::cout << "Cant load Statue sprite from Textures folder" << std::endl;
	}
}

void InteractiveObject::InitSprite()
{
	_sprite.setTexture(_texture);

	_rect_sprite = sf::IntRect(0, 0, 38, 75);

	_sprite.scale(1.5f, 1.5f);
}

// Const 
InteractiveObject::InteractiveObject(int pos_x, int pos_y)
{
	InitText();
	InitSprite();

	SetPosition(pos_x, pos_y);
}

// Dest
InteractiveObject::~InteractiveObject()
{
}



void InteractiveObject::Render(sf::RenderTarget& target)
{
	target.draw(this->_sprite);
}

void InteractiveObject::SetPosition(int pos_x, int pos_y)
{
	_sprite.setPosition(pos_x, pos_y);
}
