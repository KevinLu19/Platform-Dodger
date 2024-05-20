#pragma once

#include <SFML/Graphics.hpp>


class PlayerCamera
{
private:
	sf::View _view;
	sf::FloatRect _world_bound;
	sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t);

public:
	PlayerCamera(float width, float height, const sf::FloatRect& world_bounds);
	~PlayerCamera();

	void Update(const sf::Vector2f & target_position);
	void ApplyTo(sf::RenderWindow & window);

};

