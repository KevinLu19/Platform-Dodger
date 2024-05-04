#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


class PlayerHeart
{
private:
	sf::Sprite _heart_sprite;
	sf::Texture _heart_texture;

	sf::IntRect _rect_source_sprite;			// Specifies the rectangle around sprite.

	// Animation Parameters.
	sf::Clock _clock;
	int _num_frames, _frame_duration, _current_frame;
	int* _ptr_curr_frame;

	void InitText();
	void InitSprite();

public:
	PlayerHeart();
	~PlayerHeart();
	
	sf::Sprite GetHeartSprite();

	void Animation();
	void Render(sf::RenderWindow & target);				// Draws heart itself.

	void HeartSetPosition(double x);
};

