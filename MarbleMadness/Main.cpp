#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Entity.h"
#include "Wall.h"
#include "Bullet.h"
#include "Marble.h"
#include "Player.h"
#include "Spawner.h"
#include "Observer.h"
#include "World.h"
#include "TextInterpreter.h"

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

	World* gameWorld = new World();

	GenericSpawner* spawner = new GenericSpawner(gameWorld);

	TextInterpreter textInterpreter(spawner);

	Marble* marble = spawner->getMarble(0);
	vector <Wall*> wallVectors = spawner->getWall();

	/*
	Vector2f* spawn = new Vector2f;
	Vector2f* size = new Vector2f;
	Color* color = new Color;

	//Data that should come in through a text file
	*spawn = Vector2f(0.0f, 0.0f);
	*size = Vector2f(1920.0f, 200.0f);
	*color = Color::White;
	Wall* wall1 = new Wall(spawn, size, color, gameWorld->getWorld());

	*spawn = Vector2f(0.0f, 880.0f);
	*size = Vector2f(1920.0f, 200.0f);
	*color = Color::Cyan;
	Wall* wall2 = new Wall(spawn, size, color, gameWorld->getWorld());

	*spawn = Vector2f(0.0f, 0.0f);
	*size = Vector2f(200.0f, 1080.0f);
	*color = Color::Yellow;
	Wall* wall3 = new Wall(spawn, size, color, gameWorld->getWorld());

	*spawn = Vector2f(1720.0f, 0.0f);
	*size = Vector2f(200.0f, 1080.0f);
	*color = Color::Green;
	Wall* wall4 = new Wall(spawn, size, color, gameWorld->getWorld());

	*spawn = Vector2f(500.0f, 500.0f);
	float* circleSize = new float;
	*circleSize = 10.0f;
	*color = Color::Blue;
	Marble* marble = new Marble(spawn, circleSize, color, gameWorld->getWorld());
	*/

	//Fixed time loop
	float timeStep = 1.0f / 120.0f;
	int velocityIterations = 8;
	int positionIterations = 3;


	//Basic game loop using polling. Interrupt would be better.
	while (window.isOpen())
	{

		gameWorld->getWorld()->Step(timeStep, velocityIterations, positionIterations);

		window.pollEvent(gameEvent);

		if (gameEvent.type == Event::Closed)
		{
			window.close();
		}

		if (gameEvent.type == Event::KeyPressed)
		{
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				marble->updateLinearVelocity(b2Vec2(-1.0f, 0.0f));
			}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				marble->updateLinearVelocity(b2Vec2(1.0f, 0.0f));
			}
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				marble->updateLinearVelocity(b2Vec2(0.0f, 1.0f));
			}
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				marble->updateLinearVelocity(b2Vec2(0.0f, -1.0f));
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
		}
		else
		{
			marble->updateLinearVelocity(b2Vec2(0.0f, 0.0f));
		}

		marble->updatePosition();

		// Draw the scene!
		window.clear(Color::Black);
		for (int i = 0; i < wallVectors.size() - 1; i++)
		{
			window.draw(wallVectors[i]->getGraphicBody());
		}
		window.draw(marble->getMarbleGraphic());
		window.display();
	}
}