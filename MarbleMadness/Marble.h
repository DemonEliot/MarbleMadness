#pragma once

#include "Entity.h"
#include "Vector2.h"

using namespace std;

class Marble : public Entity
{
public:
	Marble() {};
	Marble(Vector2* spawnPosition, Vector2* objSize)
	{
		startPos = *spawnPosition; size = *objSize; currentPos = *spawnPosition;
	};


protected:
	Vector2 currentPos;
};