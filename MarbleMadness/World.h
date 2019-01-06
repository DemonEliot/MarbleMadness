#pragma once

#include <Box2D/Box2D.h>

//Physics World Class

class World{
public:
	World() 
	{
		b2Vec2 gravity(0.0f, 0.0f);
		world_ptr = new b2World(gravity);
	};

	b2World* getWorld()
	{
		return world_ptr;
	}
private:
	b2World* world_ptr;
};