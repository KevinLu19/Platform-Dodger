#include "Map.h"

void Map::InitText()
{
	if (!_map.loadFromFile("Textures/map.png"))
		std::cout << "Cannot load map.png from textures" << std::endl;
}

void Map::InitSprite()
{
	_sprite.setTexture(_map);
	_sprite.scale(2.0, 2.0f);
}

Map::Map()
{
	InitText();
	InitSprite();

	// Define collision areas to act as a wall.
	_collision_areas = std::vector<sf::IntRect>
	{
		sf::IntRect(0, 530, 600, 280),					// left, top, width, height
		sf::IntRect(0, 800, 400, 150),					// Bottom portion of the left platform.
		sf::IntRect(0, 900, 255, 500),
		sf::IntRect(280, 1200, 290, 200),
		sf::IntRect(600, 1290, 970, 300),
		sf::IntRect(1600, 1322, 300, 300),
		sf::IntRect(1950, 1295, 500, 500)
	};
}

Map::~Map()
{
}

void Map::Render(sf::RenderWindow& target)
{
	target.draw(_sprite);
}

// Using Pre-defined collision spots for collision detection to act as a "wall"
bool Map::CheckCollision(const sf::Sprite & player, const sf::Vector2f & movement)
{
	sf::FloatRect player_bound = player.getGlobalBounds();

	for (const auto& area : _collision_areas)
	{
		if (player_bound.intersects(sf::FloatRect(area)))
		{
			std::cout << "Collision detected" << std::endl;

			return true;
		}
	}

	return false;
}

// For debugging purposes.
std::vector<sf::IntRect> Map::GetCollision()
{
	return _collision_areas;
}
