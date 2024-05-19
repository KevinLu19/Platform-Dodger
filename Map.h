#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

struct CollisionRect
{
	sf::IntRect _rect;
};

class Map
{
private:
	void InitText();
	void InitSprite();

	sf::Texture _map;
	sf::Sprite _sprite;

	// Define collision areas manually.
	std::vector<CollisionRect> _collision_areas;



public:
	Map();
	~Map();

	int map_width;
	int map_height;

	void Render(sf::RenderWindow & target);

	// Checking collisions.
	void CheckCollision();
};

