#pragma once

#include "Marble.h"
#include "Vector2.h"

using namespace std;

class Player : public Marble
{
public:
	Player(Vector2* spawnPosition, Vector2* objSize)
	{
		startPos = *spawnPosition; size = *objSize; currentPos = *spawnPosition;
	};

};