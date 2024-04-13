#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
private:
	sf::Sprite _bullet_sprite;
	sf::Texture _bullet_texture;

	float _bullet_speed;
	const float velocity = 3.0f;	//Pixel per second.
	
	sf::FloatRect _bullet_bounding_box = _bullet_sprite.getGlobalBounds();

	// Private functions
	void InitTexture();
	void InitSprite();

public:
	Bullet();
	~Bullet();

	// Functions
	void Update();
	void Render(sf::RenderTarget & target);
	void Move();
	sf::Sprite GetBulletSprite();
};

