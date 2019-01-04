#pragma once
#include <iostream>

enum class EntityType { player, wall, bullet};

class Observer {
public:
	Observer() { score = 0; };
	~Observer() {};

	void updateScore(EntityType entity);
	void collision();
private:
	int score;
};

void Observer::updateScore(EntityType entity)
{
	switch (entity) 
	{
	//Need to build cases for where the player scores points (like killing enemies, and not dying) 	
		case EntityType::player:
			break;
		case EntityType::wall:
			break;
	}
}

void Observer::collision()
{

}