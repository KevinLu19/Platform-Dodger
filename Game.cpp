#include "Game.h"

// Private Functions.
void Game::InitializerVariables()
{
	this -> _window = nullptr;

}

void Game::InitWindow()
{
	_video_mode.height = 800;
	_video_mode.width = 1280;

	this -> _window = new sf::RenderWindow(this->_video_mode, "Bullet Dodger", sf::Style::Titlebar | sf::Style::Close);
	this->_window->setFramerateLimit(144);
	this->_window->setVerticalSyncEnabled(false);
}

void Game::InitPlayer()
{
	this->_player = new Player();
	this->_bullet = new Bullet();
	this->_diamond = new Diamond();

	this->_player_heart = new PlayerHeart();

	// Sets position for heart 2 and heart 3.
	this->_player_heart2 = new PlayerHeart();
	_player_heart2->HeartSetPosition(80);

	this->_player_heart3 = new PlayerHeart();
	_player_heart3->HeartSetPosition(110);


}

// Constructor
Game::Game()
{
	// Create window.
	this -> InitializerVariables();
	this -> InitWindow();

	// Import the map.
	if (!_map_texture.loadFromFile("Textures/map.png"))
	{
		std::cout << "ERROR::GAME::GAME()::can't load map.png from Texture folder." << std::endl;
	}

	// Map to sprite.
	_map_sprite.setTexture(_map_texture);

	// Sprite Entites for the game.
	this->InitPlayer();
}

// Destructor - Deletes pointer to releif memory.
Game::~Game()
{
	delete this -> _window;
	delete this->_player;
	delete this->_bullet;
	delete this->_diamond;

	delete this->_player_heart;
	delete this->_player_heart2;
	delete this->_player_heart3;
}

// Accessors
const bool Game::Running() const
{
	return this -> _window->isOpen();
}

// Functions
void Game::Run()
{
	while (this -> _window->isOpen())
	{
		this->Update();
		this->Render();
	}
}

// Collision for any 2 sprites. Uses their respective sprites to find collisions.
void Game::Collision(sf::Sprite player_sprite, sf::Sprite bullet_sprite)
{
	// Handles the collisions between 2 sprites aka Bullet and player sprite.
	if (player_sprite.getGlobalBounds().intersects(bullet_sprite.getGlobalBounds()))
	{
		std::cout << "Bullet hit Player" << std::endl;

		// Animate player hurt sprite.
		_player->AnimateHurt();

		// Reduce heart by 1.
		//_player->TakeDamage();
	}
}

void Game::Update()
{
	// Everything that doesn't have to do with drawing but have to do with behind the scene logic (ex: moving) goes here.
	// Here is where the game is at.
	sf::Event e;
	while (this->_window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->_window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->_window->close();
	}

	// Player Heart Animation.
	_player_heart->Animation();
	_player_heart2->Animation();
	_player_heart3->Animation();


	_diamond->DiamondAnimate();

	// //Move Player - Old
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->_player->Move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->_player->Move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->_player->Move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->_player->Move(0.f, 1.f);*/

	_player->Update();		// Handles player movement and animation.
	

	Collision(_player->GetSprite(), _bullet->GetBulletSprite());

	// Make bullet(s) travel across the screen by updating its position using set velocity.
	_bullet->Move();
}


void Game::Render()
{
	// visualizing all positions. 
	this -> _window -> clear();

	// Draw game
	_window->draw(_map_sprite);					// Map
	
	_player_heart->Render(*this-> _window);		// Player heart
	_player_heart2->Render(*this-> _window);
	_player_heart3->Render(*this->_window);
	
	_diamond->Render(*this-> _window);	


	this->_bullet->Render(*this -> _window);
	this->_player->Render(*this->_window);

	
	// Display everything above.
	this->_window->display();
}


