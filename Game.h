#pragma once

#include "Player.h"
#include "Bullet.h"
#include "Diamond.h"
#include <vector>
#include "InteractiveObject.h"
#include "Map.h"
#include <iostream>
#include "PlayerCamera.h"

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

	// Platform for the game.
	//Platform * _platform;

	// Different Classes.
	Player* _player;	
	Bullet* _bullet;
	Diamond* _diamond;
	InteractiveObject * _game_obj;

	PlayerCamera * _player_camera;
	sf::View hud_view;

	Map * _map;

	// 3 Lives total for the player.
	PlayerHeart * _player_heart;
	std::vector<PlayerHeart> _hearts;			// Holds the hearts.
	int _health;


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