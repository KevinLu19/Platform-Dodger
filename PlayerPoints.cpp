#include "PlayerPoints.h"

// Const
PlayerPoints::PlayerPoints()
{
	_player_score = 0;			// Player score count is 0 from the start.
}

// Dest
PlayerPoints::~PlayerPoints()
{
}


// Increases player score by 1.
int PlayerPoints::IncreaseScore()
{
	return _player_score + 1;
}