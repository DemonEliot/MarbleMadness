#pragma once

#include "Entity.h"

class Wall : public Entity
{
public:
	Wall(Vector2f* spawnPosition, Vector2f* objSize, Color* newColor, b2World* world)
	{
		startPos = *spawnPosition; size = *objSize; color = *newColor;
		wallGraphic.setSize(size);
		wallGraphic.setFillColor(color);
		wallGraphic.setPosition(startPos);

		scalingFactor = 200.0f;

		//Wall colliders
		float wallHalfWidth = (size.x/200)/2;
		float wallHalfHeight = (size.y/200)/2;
		
		b2PolygonShape wallBox;
		wallBox.SetAsBox(wallHalfWidth, wallHalfHeight);

		b2BodyDef wallBodyDef;
		wallBodyDef.position.Set((startPos.x + size.x/2) / scalingFactor, (startPos.y + size.y/2) / scalingFactor * -1.0f);

		b2Body* wallBody = world->CreateBody(&wallBodyDef);

		wallBody->CreateFixture(&wallBox, 0.0f);

		wallPhysicsPosition = wallBody->GetPosition();

		wallGraphicsPosition.x = (wallPhysicsPosition.x - wallHalfWidth) * scalingFactor;
		wallGraphicsPosition.y = (wallPhysicsPosition.y + wallHalfHeight) * scalingFactor * -1.0f;

		wallGraphic.setPosition(wallGraphicsPosition.x, wallGraphicsPosition.y);
	};
	~Wall() {};

	RectangleShape getGraphicBody()
	{
		return wallGraphic;
	}

	Vector2f getPosition()
	{
		return startPos;
	}

	Vector2f getPhysicalPos()
	{
		return physicsPos;
	}

private:
	RectangleShape wallGraphic;
	Vector2f wallGraphicsPosition;
	b2Vec2 wallPhysicsPosition;
	Color color;
	Vector2f size;
	Vector2f physicsPos;
};