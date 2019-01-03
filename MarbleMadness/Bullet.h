#pragma once

#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet(Vector2f* spawnPosition, Vector2f* objSize)
	{
		startPos = *spawnPosition; size = *objSize; currentPos = *spawnPosition;
	};


private:
	Vector2f currentPos;
	Entity* bulletOrigin;
	Vector2f size;
};