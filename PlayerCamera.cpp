#include "PlayerCamera.h"
#include <algorithm>

sf::Vector2f PlayerCamera::lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t)
{
    return start + t * (end - start);
}

// Const
PlayerCamera::PlayerCamera(float width, float height, const sf::FloatRect & world_bounds)
	: _view(sf::FloatRect(0.f, 0.f, width, height)), _world_bound(world_bounds)
{
	_view.setCenter(width / 2.f, height / 2.f);
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::Update(const sf::Vector2f& target_position)
{
    // Calculate the target center position
    sf::Vector2f targetCenter = target_position;

    // Clamp the target center to the world bounds
    targetCenter.x = std::max(_view.getSize().x / 2.f, std::min(targetCenter.x, _world_bound.width - _view.getSize().x / 2.f));
    targetCenter.y = std::max(_view.getSize().y / 2.f, std::min(targetCenter.y, _world_bound.height - _view.getSize().y / 2.f));

    // Smoothly move the view towards the target center
    _view.setCenter(lerp(_view.getCenter(), targetCenter, 0.1f));
}

void PlayerCamera::ApplyTo(sf::RenderWindow & window)
{
    window.setView(_view);
}
