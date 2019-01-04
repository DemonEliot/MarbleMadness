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
			Wall* wall = new Wall(spawn, size, color, gameWorld->getWorld());
			spawnWalls.push_back(wall);
		}
		else if (entity == "Marble")
		{
			*spawn = Vector2f(fVector[0], fVector[1]);
			*circleSize = float(fVector[2]);
			*color = textColor;
			Marble* marble = new Marble(spawn, circleSize, color, gameWorld->getWorld());
			spawnMarbles.push_back(marble);
		}
		else
		{
			cerr << "Something went wrong with parsing in the text file into the spawner!" << endl;
			exit(1);
		}
	}
	//void addPrototype(Entity* newPrototype) { spawnPrototypes.push_back(newPrototype); };
	//Entity* getPrototype(int i) { return spawnPrototypes.at(i); };

	Wall* getWall(int i) { return spawnWalls[i]; };
	vector <Wall*> getWall() { return spawnWalls; };
	Marble* getMarble(int i) { return spawnMarbles[i]; };
	vector <Marble*> getMarble() { return spawnMarbles; };

private:
	//vector<Entity*> spawnPrototypes;
	vector<Wall*> spawnWalls;
	vector<Marble*> spawnMarbles;
	Vector2f* spawn;
	Vector2f* size;
	Color* color;
	float* circleSize;
	World* gameWorld;
};

GenericSpawner::~GenericSpawner()
{
	while (spawnWalls.size() != 0)
	{
		delete spawnWalls.back();
		spawnWalls.pop_back();
	}
	while (spawnMarbles.size() != 0)
	{
		delete spawnMarbles.back();
		spawnMarbles.pop_back();
	}
	delete spawn;
	delete size;
	delete color;
	delete circleSize;
}
