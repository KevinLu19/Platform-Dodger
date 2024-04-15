#include "Bullet.h"

// Private

void Bullet::InitTexture()
{
	// Load texture from file.
	if (!this->_bullet_texture.loadFromFile("Textures/bullet.png"))
	{
		std::cout << "ERROR::BULLET::INITTEXTURE::Could not load bullet.png from file." << std::endl;
	}
}

void Bullet::InitSprite()
{
	// Set the texture to sprite.
	this->_bullet_sprite.setTexture(this->_bullet_texture);
	// Resize if needed.
	this->_bullet_sprite.scale(.15f, .15f);

	_bullet_sprite.setPosition(0.f, 300.f);
}

// Const / Dest
Bullet::Bullet()
{
	this->InitTexture();
	this->InitSprite();
	this->_bullet_speed = 20.f;
}

Bullet::~Bullet()
{

}


// Functions
void Bullet::Update()
{

}

void Bullet::Render(sf::RenderTarget& target)
{
	target.draw(this->_bullet_sprite);
}

void Bullet::Move()
{

	_bullet_sprite.move(velocity, 0.f);
}

sf::Sprite Bullet::GetBulletSprite()
{
	return _bullet_sprite;
}
