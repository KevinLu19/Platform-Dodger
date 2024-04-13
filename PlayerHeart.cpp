#include "PlayerHeart.h"

// Private Functions.
void PlayerHeart::InitText()
{
	if (_heart_texture.loadFromFile("Textures/Heart.png"))
		std::cout << "Cannot load Heart.png onto PlayerHeart::InitText()" << std::endl;
}

void PlayerHeart::InitSprite()
{
	_heart_sprite.setTexture(_heart_texture);
}

// Const / Destructor
PlayerHeart::PlayerHeart()
{
	InitText();
	InitSprite();
	_num_hearts = 3;	// 3 total hearts for the player.

	_heart_sprite.setPosition(50.f, 60.f);			// Permanent position for the heart for player.
	_heart_sprite.scale(2.f, 2.f);
}

PlayerHeart::~PlayerHeart()
{

}

// Functions.
sf::Sprite PlayerHeart::GetHeartSprite()
{
	return _heart_sprite;
}

void PlayerHeart::Animation()
{

}
