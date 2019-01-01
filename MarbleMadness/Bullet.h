#pragma once

#include "Entity.h"
#include "Vector2.h"

using namespace std;

class Bullet : public Entity
{
public:
	Bullet(Vector2* spawnPosition, Vector2* objSize)
	{
		startPos = *spawnPosition; size = *objSize; currentPos = *spawnPosition;
	};


private:
	Vector2 currentPos;
	Entity* bulletOrigin;
};