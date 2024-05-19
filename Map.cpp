#include "Map.h"

void Map::InitText()
{
	if (!_map.loadFromFile("Textures/map.png"))
		std::cout << "Cannot load map.png from textures" << std::endl;
}

void Map::InitSprite()
{
	_sprite.setTexture(_map);
	_sprite.scale(2.7f, 1.8f);
}

Map::Map()
{
	InitText();
	InitSprite();

}

Map::~Map()
{
}

void Map::Render(sf::RenderWindow& target)
{
	target.draw(_sprite);
}


void Map::CheckCollision()
{
	
}
