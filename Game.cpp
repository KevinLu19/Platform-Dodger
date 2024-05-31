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
	this->_map = new Map();
	this->_player = new Player();
	this->_bullet = new Bullet();
	this->_diamond = new Diamond();
	
	// Creating player camera.
	// Define world boundaries.
	sf::FloatRect world_bounds(0.f, 0.f, 2500.f, 2000.f);					// Starts origin 0,0. 1600 units extend to right.
	this->_player_camera = new PlayerCamera(800.f, 600.f, world_bounds);
	
	// Create HUD view (same size as window)
	hud_view = sf::View(sf::FloatRect(0.f, 0.f, 800.f, 600.f));

	this->_game_obj = new InteractiveObject(950, 550);


	_health = 3;												// 3 lives for the player.

	// Store PlayerHeart Objects.
	for (int i = 0; i < _health; ++i)
	{
		_player_heart = new PlayerHeart();
		_player_heart->HeartSetPosition((i * 30) + 50);			// Sets position for each of the heart.

		_hearts.push_back(* _player_heart);						// Pushback will call the constructor. Emplace_back will not.
	}
}

// Constructor
Game::Game()
{
	// Create window.
	this -> InitializerVariables();
	this -> InitWindow();

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
	delete this->_game_obj;

	//delete this->_platform;

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

// Collision for any 2 sprites. Uses their respective sprites to find collisions.
void Game::Collision(sf::Sprite player_sprite, sf::Sprite bullet_sprite)
{
	// Handles the collisions between 2 sprites aka Bullet and player sprite.
	if (player_sprite.getGlobalBounds().intersects(bullet_sprite.getGlobalBounds()))
	{
		//std::cout << "Bullet hit Player" << std::endl;

		// Animate player hurt sprite.
		_player->AnimateHurt();

		// Reduce heart by 1.
		_player->TakeDamage(_health, _hearts);
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

	// Animate hearts in the hearts vector.
	for (auto& heart : _hearts)
	{
		heart.Animation();
	}


	_diamond->DiamondAnimate();

	_player->Update();												// Handles player movement and animation.
	_player_camera->Update(_player->GetSprite().getPosition());		// Update camera to follow player.

	Collision(_player->GetSprite(), _bullet->GetBulletSprite());

	// Make bullet(s) travel across the screen by updating its position using set velocity.
	_bullet->Move();
}


void Game::Render()
{
	// visualizing all positions. 
	this -> _window -> clear();

	// Draw game
	_map->Render(*this->_window);												// Map
	
	_player_camera->ApplyTo(*this->_window);									// Apply camera view to window.
	_window->setView(hud_view);

	// Render all the hearts in the heart vector.
	for (auto & hearts : _hearts)
	{
		hearts.Render(*this->_window);
	}


	_player_camera->ApplyTo(*this->_window);


	//// Draw Collision areas for debugging purposes.
	//for (const auto& area : _map->GetCollision())
	//{
	//	sf::RectangleShape rect;
	//	
	//	rect.setPosition(static_cast<float>(area.left), static_cast<float>(area.top));
	//	rect.setSize(sf::Vector2f(static_cast<float>(area.width), static_cast<float>(area.height)));
	//	rect.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red
	//	
	//	this->_window->draw(rect);
	//}


	// Draw everything else.
	_game_obj->Render(*this->_window);											// Statue that will be an interactive obj.
	_diamond->Render(*this-> _window);	


	this->_bullet->Render(*this -> _window);
	this->_player->Render(*this->_window);
	
	// Display everything above.
	this->_window->display();
}


