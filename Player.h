#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "PlayerHeart.h"
#include <vector>
#include "InteractiveObject.h"


class Player : PlayerHeart
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

	// Handling Speed/velocity
	float _movement_speed;
	float _velocity_x, _velocity_y;						// Velocity of the player sprite.
	float _gravity;										// Set gravity for the game.
	float _jump_height;
	float _position_x, _position_y;						// Position of the character.
	sf::Vector2f _movement;
	sf::Vector2f _velocity;
	float delta_time;

	// For Jumping
	float _jump_velocity;
	bool _is_jumping;

	bool _heart_taken;									// Used for TakeDamage(). Used for allowing only one heart to be taken.

	sf::FloatRect _player_bounding_box = _sprite.getGlobalBounds();

	// Tracking health of the player.
	PlayerHeart * _player_heart;
	
	// Variable used for sprite animation.
	int _current_frame;
	int _num_frames;
	int _frame_duration;
	sf::IntRect _rect_sprite;
	int _frame_width;

	// For dashes sprite. Sprite sheet starts at 0.
	sf::IntRect frame_3_rect;
	sf::IntRect frame_4_rect;

	// For Interactive Objects such as statues
	InteractiveObject * _interactive_obj;

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

	void AnimateHurt();

	void TakeDamage(int& health, std::vector<PlayerHeart> & _hearts);
	
	void PowerUp(sf::Sprite immoveable_obj_sprite);
};

