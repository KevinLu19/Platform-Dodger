#include "DiamondItem.h"

// Const
DiamondItem::DiamondItem()
{
	std::string texture = "Textures/Diamond.png";
	_num_frames = 10;
	_current_frame = 0;
	_frame_width = 17;

	_animation = new Animation(texture, _num_frames, 17, 12);
}

// Dest
DiamondItem::~DiamondItem()
{
	delete this->_animation;
}

void DiamondItem::Animate()
{
	_sprite = _animation->AnimateSpriteSheetSeconds();
}

void DiamondItem::Render(sf::RenderTarget& target)
{
	target.draw(_sprite);
}
