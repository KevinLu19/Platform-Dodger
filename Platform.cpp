#include "Platform.h"

// Private functions.
void Platform::InitText()
{
	if (!_platform_text.loadFromFile("Textures/platform.png"))
		std::cout << "Cannot load platform.png from textures folder." << std::endl;
}

void Platform::InitSprite()
{
	_platform_sprite.setTexture(_platform_text);

	_platform_sprite.scale(2.f, 2.f);

	_platform_rect = sf::IntRect(0, 0, 500, 500);
	_platform_sprite.setTextureRect(_platform_rect);			// Binds bounding box to sprite.
}

// Const
Platform::Platform(sf::Vector2f position)
{
	InitText();
	InitSprite();

	_platform_sprite.setPosition(position);
}

// Dest
Platform::~Platform()
{
}

void Platform::Render(sf::RenderWindow& target)
{
	target.draw(_platform_sprite);
}