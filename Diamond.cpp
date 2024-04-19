#include "Diamond.h"

// Private Functions

void Diamond::InitText()
{
	if (!_diamond_text.loadFromFile("Textures/Diamond.png"))
	{
		std::cout << "Cannot load Diamond.png from DIAMOND::InitText() in Diamond.cpp" << std::endl;
	}
}

void Diamond::InitSprite()
{
	_diamond_sprite.setTexture(_diamond_text);

	_diamond_sprite.scale(2.f, 2.f);

	this->_rect_source_sprite = sf::IntRect(0,0, 17, 12);					// x, y, w, h
	_diamond_sprite.setTextureRect(_rect_source_sprite);
}

// Const
Diamond::Diamond()
{
	InitText();
	InitSprite();

	//_animation = new Animation("Textures/Diamond.png", 10, 10);

	_num_frames = 10;
	_current_frame = 0;

	// Example location for diamond.
	_diamond_sprite.setPosition(90.f, 90.f);

	_frame_width = _diamond_text.getSize().x / 10;
}

// Dest
Diamond::~Diamond()
{
	delete this -> _animation;
}

// Functions

void Diamond::DiamondAnimate()
{
	if (_clock.getElapsedTime().asSeconds() > .30f)
	{
		// Advance to next frame.
		_current_frame = (_current_frame + 1) % _num_frames;
		
		
		// Update texture rectangle.
		_rect_source_sprite.left = _current_frame * _frame_width;			// Current Frame * frame Width.
		_diamond_sprite.setTextureRect(_rect_source_sprite);

		_clock.restart();
	}
}

void Diamond::Render(sf::RenderTarget& target)
{
	target.draw(this->_diamond_sprite);
}
