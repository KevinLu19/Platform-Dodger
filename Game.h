#pragma once

#include "Player.h"
#include "Bullet.h"
#include "Diamond.h"

/*
	Game class acts like a game engine.

	Wrapper class.
*/

class Game
{
private:
	// Window
	sf::RenderWindow * _window;			// Want to delete this window whenever we want. Hence dynamically allocated windows variable.
	sf::VideoMode _video_mode;

	sf::Texture _map_texture;
	sf::Sprite _map_sprite;

	// Different Classes.
	Player* _player;	
	Bullet* _bullet;
	Diamond* _diamond;

	// 3 Lives total for the player.
	PlayerHeart* _player_heart;


	void InitializerVariables();
	void InitWindow();
	void InitPlayer();
	
public:
	// Constructor + Destructor
	Game();
	~Game();

	// Accessors
	const bool Running() const;

	// Functions
	void Update(); 
	void Render();
	void Run();
	void Collision(sf::Sprite player_sprite, sf::Sprite bullet_sprite);
};