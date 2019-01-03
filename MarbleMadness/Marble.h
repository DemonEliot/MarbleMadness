#pragma once

#include "Entity.h"

class Marble : public Entity
{
public:
	Marble() {};
	Marble(Vector2f* spawnPosition, float* objSize, Color* newColor, b2World* world)
	{
		startPos = *spawnPosition; size = *objSize; color = *newColor;
		marble.setRadius(size);
		marble.setFillColor(color);
		marble.setPosition(startPos);

		scalingFactor = 200.0f;
		circleRadius = 0.05f;

		// Marble collider
		b2CircleShape marbleCircle;
		marbleCircle.m_radius = circleRadius;

		//BodyDef is a placeholder whose properties will be bound to a physics body
		//Also, need to reverse the y axis to - because of SMFL.
		b2BodyDef marbleBodyDef;
		marbleBodyDef.type = b2_dynamicBody;
		marbleBodyDef.position.Set((startPos.x + size) / scalingFactor, (startPos.y + size) / scalingFactor * -1.0f);
		//marbleBodyDef.position.Set(2.55f, -2.55f);

		marbleBody = world->CreateBody(&marbleBodyDef);

		b2FixtureDef marbleFixtureDef;
		marbleFixtureDef.shape = &marbleCircle;
		marbleFixtureDef.density = 0.3f;
		marbleFixtureDef.friction = 0.3f;

		//This connects the body with the collision shape defined earlier.
		marbleBody->CreateFixture(&marbleFixtureDef);

		updatePosition();
	};

	void updatePosition()
	{
		marblePhysicsPosition = marbleBody->GetPosition();

		marbleGraphicsPosition.x = (marblePhysicsPosition.x - circleRadius) * scalingFactor;
		marbleGraphicsPosition.y = (marblePhysicsPosition.y + circleRadius) * scalingFactor * -1.0f;

		marble.setPosition(marbleGraphicsPosition.x, marbleGraphicsPosition.y);
	}

	void updateLinearVelocity(b2Vec2 newVelocity)
	{
		marbleBody->SetLinearVelocity(newVelocity);
	}

	CircleShape getMarbleGraphic()
	{
		return marble;
	}

	b2Body* getMarbleBody()
	{
		return marbleBody;
	}

protected:
	CircleShape marble;
	b2Body* marbleBody;
	float size;
	Color color;
	Vector2f marbleGraphicsPosition;
	b2Vec2 marblePhysicsPosition;
	float circleRadius;
};