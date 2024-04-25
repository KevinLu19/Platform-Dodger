#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "PlayerHeart.h"

class Player
{
private:
	sf::Sprite _sprite;
	sf::Texture _texture;

	sf::Clock _clock;

	// Textures for different positions.
	sf::Texture _idle;
	sf::Texture _jump;
	sf::Texture _landing;
	sf::Texture _dash_right;
	sf::Texture _dash_left;
	sf::Texture _powerup;
	sf::Texture _falling;
	sf::Texture _hurt;

	float _movement_speed;
	float _velocity_x = 3.f, _velocity_y = 1.5f;		// Velocity of the player sprite.
	float _gravity = 0.5f;								// Set gravity for the game.
	

	sf::FloatRect _player_bounding_box = _sprite.getGlobalBounds();

	PlayerHeart * _player_heart;
	
	// Variable used for sprite animation.
	int _current_frame;
	int _num_frames;
	int _frame_duration;
	sf::IntRect _rect_sprite;
	int _frame_width;

	// For dashes sprite.
	sf::IntRect frame_3_rect;
	sf::IntRect frame_4_rect;

	// Private Functions
	void initTexture();
	void initSprite();

public:
	Player();
	~Player();

	//Functions
	void Update();
	void Render(sf::RenderTarget& target);
	void Move(float dir_x, float dir_y);

	sf::Sprite GetSprite();

	void Animate(int num_frames);
	void AnimateDash();

	int GetFrameWidth(sf::Texture & texture, int frames);
	
	void OnJumpKeyPressed();
	void OnJumpKeyReleased();
};

