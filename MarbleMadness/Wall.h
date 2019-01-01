#pragma once

#include "Entity.h"
#include "Vector2.h"

using namespace std;

class Wall : public Entity
{
public:
	Wall(Vector2* spawnPosition, Vector2* objSize)
	{
		startPos = *spawnPosition; size = *objSize;
	};
	
};