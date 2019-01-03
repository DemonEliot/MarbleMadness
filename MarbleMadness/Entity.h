#pragma once

#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>

using namespace std;
using namespace sf;

class Entity {
public:
	Entity() {};
	Entity(Vector2f* spawnPosition, b2World* world) 
	{ startPos = *spawnPosition;};
	virtual ~Entity() {};

protected:
	Vector2f startPos;
	float scalingFactor;
};