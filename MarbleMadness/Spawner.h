#pragma once

#include <vector>
#include "Entity.h"

using namespace std;

class Spawner {
public:
	Spawner() {};
	~Spawner() 
	{
		//Should let resouce manager handle this
		//Deconstructor: while there's entities left, delete and pop back the last one
		while (spawnedEntities.size() != 0)
		{
			delete spawnedEntities.back();
			spawnedEntities.pop_back();
		}
	};

	void addEntity(Entity* newPrototype) 
	{ 
		spawnedEntities.push_back(newPrototype); 
	};

	Entity* getEntity(int i)
	{ 
		if (spawnedEntities.size() - 1 < i)
		{
			throw std::out_of_range("Tried to access out of the range of the current vector size!");
		}
		else 
		{ 
			return spawnedEntities[i];
		}
		
	};

private:
	vector<Entity*> spawnedEntities;
};