#pragma once

#include "Marble.h"

class Player : public Marble
{
public:
	Player(Vector2f* spawnPosition, float* objSize)
	{
		startPos = *spawnPosition; size = *objSize;
	};

};