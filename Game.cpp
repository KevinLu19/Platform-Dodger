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
	this -> _player = new Player();
	this->_bullet = new Bullet();
	this->_player_heart = new PlayerHeart();
}

// Constructor
Game::Game()
{
	// Create window.
	this -> InitializerVariables();
	this -> InitWindow();

	// Import the map.
	if (!_map_texture.loadFromFile("Textures/map.jpg"))
	{
		std::cout << "ERROR::GAME::GAME()::can't load map.jpg from Texture folder." << std::endl;
	}

	// Map to sprite.
	_map_sprite.setTexture(_map_texture);

	this->InitPlayer();
}

// Destructor
Game::~Game()
{
	delete this -> _window;
	delete this->_player;
	delete this->_bullet;
	delete this->_player_heart;
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

void Game::Collision(sf::Sprite player_sprite, sf::Sprite bullet_sprite)
{
	// Handles the collisions between 2 sprites aka Bullet and player sprite.
	if (player_sprite.getGlobalBounds().intersects(bullet_sprite.getGlobalBounds()))
	{
		// For testing, want the player sprite to move up inicating collision occured.
		this->_player->Move(0.f, -10.f);
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

	 //Move Player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->_player->Move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->_player->Move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->_player->Move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->_player->Move(0.f, 1.f);

	// Bullet and player collision detection.
	if (_bullet->GetBulletSprite().getGlobalBounds().intersects(_player->GetSprite().getGlobalBounds()))
	{
		std::cout << "Bullet collision and Player sprite has occured" << std::endl;

		// For testing, want the player sprite to move up inicating collision occured.
		this->_player->Move(0.f, -10.f);
	}

	// Make bullet(s) travel across the screen by updating its position using set velocity.
	_bullet->Move();
}


void Game::Render()
{
	// visualizing all positions. 
	this -> _window -> clear();

	// Draw game
	_window->draw(_map_sprite);		// Map
	_window->draw(this->_player_heart->GetHeartSprite());
	
	this->_bullet->Render(*this -> _window);
	this->_player->Render(*this->_window);

	
	// Display everything above.
	this->_window->display();
}


