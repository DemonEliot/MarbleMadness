#include <iostream>
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Entity.h"
#include "Wall.h"
#include "Bullet.h"
#include "Marble.h"
#include "Player.h"
#include "Spawner.h"
#include "Observer.h"

using namespace std;
using namespace sf;

void main()
{
	/* 
	Render the game window.
	myEvent is populated whenever something happens that SFML considers an event
	e.g. mouse clicks, key pressing, etc.
	*/
	RenderWindow window(VideoMode(1920, 1080), "Game Window");
	Event gameEvent;

	// Creating the shapes and setting size, position, colour...
	RectangleShape wall1, wall2, wall3, wall4;
	CircleShape marble;

	wall1.setSize(Vector2f(1920.0f, 200.0f));
	wall1.setFillColor(Color::White);
	wall1.setPosition(0, 0);

	wall2.setSize(Vector2f(1920.0f, 200.0f));
	wall2.setFillColor(Color::White);
	wall2.setPosition(0, 880);

	wall3.setSize(Vector2f(200.0f, 1080.0f));
	wall3.setFillColor(Color::White);
	wall3.setPosition(0, 0);

	wall4.setSize(Vector2f(200.0f, 1080.0f));
	wall4.setFillColor(Color::White);
	wall4.setPosition(1720, 0);

	marble.setRadius(10.f);
	marble.setFillColor(Color::Blue);
	marble.setPosition(500, 500);

	//Example for physics. See week 8 sample code for more information.
	b2Vec2 gravity(0.0f, 0.0f);
	b2World world(gravity);

	float scalingFactor = 200.0f;
	float circleRadius = 0.05f;

	// Marble collider
	b2CircleShape marbleCircle;
	marbleCircle.m_p.Set(2.5f, -2.5f);
	marbleCircle.m_radius = circleRadius;

	//BodyDef is a placeholder whose properties will be bound to a physics body
	//Also, need to reverse the y axis to - because of SMFL.
	b2BodyDef marbleBodyDef;
	marbleBodyDef.type = b2_dynamicBody;
	marbleBodyDef.position.Set(2.5f, -2.5f);

	b2Body* marbleBody = world.CreateBody(&marbleBodyDef);

	b2FixtureDef marbleFixtureDef;
	marbleFixtureDef.shape = &marbleCircle;
	marbleFixtureDef.density = 0.3f;
	marbleFixtureDef.friction = 0.3f;

	//This connects the body with the collision shape defined earlier.
	marbleBody->CreateFixture(&marbleFixtureDef);

	b2Vec2 marblePhysicsPosition = marbleBody->GetPosition();

	Vector2f marbleGraphicsPosition;

	marbleGraphicsPosition.x = (marblePhysicsPosition.x - circleRadius) * scalingFactor;
	marbleGraphicsPosition.y = (marblePhysicsPosition.y + circleRadius) * scalingFactor * -1.0f;

	marble.setPosition(marbleGraphicsPosition);

	//Wall colliders
	float wallHalfWidth = 4.8f;
	float wallHalfHeight = 0.5f;

	float wallHalfWidth2 = 0.5f;
	float wallHalfHeight2 = 2.7f;

	b2PolygonShape wallBox, wallBox2, wallBox3, wallBox4;
	wallBox.SetAsBox(wallHalfWidth, wallHalfHeight);
	wallBox2.SetAsBox(wallHalfWidth, wallHalfHeight);
	wallBox3.SetAsBox(wallHalfWidth2, wallHalfHeight2);
	wallBox4.SetAsBox(wallHalfWidth2, wallHalfHeight2);

	//Need to make for all 4 walls

	b2BodyDef wallBodyDef, wallBodyDef2, wallBodyDef3, wallBodyDef4;
	wallBodyDef.position.Set(7.5f, -3.0f);
	wallBodyDef2.position.Set(7.5f, -7.4f);
	wallBodyDef3.position.Set(3.0f, -5.0f);
	wallBodyDef4.position.Set(11.6f, -5.0f);

	b2Body* wallBody = world.CreateBody(&wallBodyDef);
	b2Body* wallBody2 = world.CreateBody(&wallBodyDef2);
	b2Body* wallBody3 = world.CreateBody(&wallBodyDef3);
	b2Body* wallBody4 = world.CreateBody(&wallBodyDef4);

	wallBody->CreateFixture(&wallBox, 0.0f);
	wallBody2->CreateFixture(&wallBox2, 0.0f);
	wallBody3->CreateFixture(&wallBox3, 0.0f);
	wallBody4->CreateFixture(&wallBox4, 0.0f);

	b2Vec2 wallPhysicsPosition = wallBody->GetPosition();
	b2Vec2 wallPhysicsPosition2 = wallBody2->GetPosition();
	b2Vec2 wallPhysicsPosition3 = wallBody3->GetPosition();
	b2Vec2 wallPhysicsPosition4 = wallBody4->GetPosition();

	Vector2f wallGraphicsPosition;
	Vector2f wallGraphicsPosition2;
	Vector2f wallGraphicsPosition3;
	Vector2f wallGraphicsPosition4;

	wallGraphicsPosition.x = (wallPhysicsPosition.x - wallHalfWidth)*scalingFactor;
	wallGraphicsPosition.y = (wallPhysicsPosition.y + wallHalfHeight)*scalingFactor*-1.0f;
	wallGraphicsPosition2.x = (wallPhysicsPosition2.x - wallHalfWidth)*scalingFactor;
	wallGraphicsPosition2.y = (wallPhysicsPosition2.y + wallHalfHeight)*scalingFactor*-1.0f;
	wallGraphicsPosition3.x = (wallPhysicsPosition3.x - wallHalfWidth2)*scalingFactor;
	wallGraphicsPosition3.y = (wallPhysicsPosition3.y + wallHalfHeight2)*scalingFactor*-1.0f;
	wallGraphicsPosition4.x = (wallPhysicsPosition4.x - wallHalfWidth2)*scalingFactor;
	wallGraphicsPosition4.y = (wallPhysicsPosition4.y + wallHalfHeight2)*scalingFactor*-1.0f;

	//Fixed time loop
	float timeStep = 1.0f / 120.0f;
	int velocityIterations = 8;
	int positionIterations = 3;


	//Basic game loop using polling. Interrupt would be better.
	while (window.isOpen())
	{

		world.Step(timeStep, velocityIterations, positionIterations);

		window.pollEvent(gameEvent);

		if (gameEvent.type == Event::Closed)
		{
			window.close();
		}

		if (gameEvent.type == Event::KeyPressed)
		{
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				marbleBody->SetLinearVelocity(b2Vec2(-0.1f, 0.0f));
			}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				marbleBody->SetLinearVelocity(b2Vec2(0.1f, 0.0f));
			}
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				marbleBody->SetLinearVelocity(b2Vec2(0.0f, 0.1f));
			}
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				marbleBody->SetLinearVelocity(b2Vec2(0.0f, -0.1f));
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
		}
		else
		{
			marbleBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		}

		marblePhysicsPosition = marbleBody->GetPosition();
		marbleGraphicsPosition.x = (marblePhysicsPosition.x - circleRadius)*scalingFactor;
		marbleGraphicsPosition.y = (marblePhysicsPosition.y + circleRadius)*scalingFactor * -1.0f;

		marble.setPosition(marbleGraphicsPosition);

		// Draw the scene!
		window.clear(Color::Black);
		window.draw(wall1);
		window.draw(wall2);
		window.draw(wall3);
		window.draw(wall4);
		window.draw(marble);
		window.display();
	}
}