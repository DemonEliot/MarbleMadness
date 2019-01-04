#pragma once

#include <vector>
#include "Entity.h"

class GenericSpawner {
public:
	GenericSpawner(World* world) { gameWorld = world; };
	~GenericSpawner();

	void createFromText(string entity, vector <float> fVector, Color textColor )
	{
		if (entity == "Wall")
		{
			*spawn = Vector2f(fVector[0], fVector[1]);
			*size = Vector2f(fVector[2], fVector[3]);
			*color = textColor;
			Wall* wall1 = new Wall(spawn, size, color, gameWorld->getWorld());
			spawnPrototypes.push_back(wall1);
		}
		else if (entity == "Marble")
		{
			*spawn = Vector2f(fVector[0], fVector[1]);
			*circleSize = float(fVector[2]);
			*color = textColor;
			Marble* marble1 = new Marble(spawn, circleSize, color, gameWorld->getWorld());
			spawnPrototypes.push_back(marble1);
		}
		else
		{
			cerr << "Something went wrong with parsing in the text file into the spawner!" << endl;
			exit(1);
		}
	}
	void addPrototype(Entity* newPrototype) { spawnPrototypes.push_back(newPrototype); };
	Entity* getPrototype(int i) { return spawnPrototypes.at(i); };

private:
	vector<Entity*> spawnPrototypes;
	Vector2f* spawn = new Vector2f;
	Vector2f* size = new Vector2f;
	Color* color = new Color;
	float* circleSize = new float;
	World* gameWorld;
};

GenericSpawner::~GenericSpawner()
{
	while (spawnPrototypes.size() != 0)
	{
		delete spawnPrototypes.back();
		spawnPrototypes.pop_back();
	}
	delete spawn;
	delete size;
	delete color;
	delete circleSize;
}
