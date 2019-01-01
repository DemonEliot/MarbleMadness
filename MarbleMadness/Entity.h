#pragma once

#include "Vector2.h"

using namespace std;

class Entity {
public:
	Entity() {};
	Entity(Vector2* spawnPosition, Vector2* objSize) 
	{ startPos = *spawnPosition; size = *objSize; };
	virtual ~Entity() {};

protected:
	Vector2 startPos;
	Vector2 size;
};