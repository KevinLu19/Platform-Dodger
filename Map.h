#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>


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
	std::vector<sf::IntRect> _collision_areas;



public:
	Map();
	~Map();

	int map_width;
	int map_height;

	void Render(sf::RenderWindow & target);

	// Checking collisions.
	bool CheckCollision(const sf::Sprite & player, const sf::Vector2f & movement);

	std::vector<sf::IntRect> GetCollision();							// For debugging purposes.
};

