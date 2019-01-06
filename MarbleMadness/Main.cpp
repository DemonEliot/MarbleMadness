#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include <enet\enet.h>

#include "Entity.h"
#include "Wall.h"
#include "Bullet.h"
#include "Marble.h"
#include "Player.h"
#include "Spawner.h"
#include "Observer.h"
#include "World.h"
#include "TextInterpreter.h"
#include "Client.h"

using namespace std;
using namespace sf;

void main()
{
	/* 
	Render the game window.
	myEvent is populated whenever something happens that SFML considers an event
	e.g. mouse clicks, key pressing, etc.
	*/
	//RenderWindow window(VideoMode(1920, 1080), "Game Window");
	//Event gameEvent;

	World* gameWorld = new World();

	GenericSpawner* spawner = new GenericSpawner(gameWorld);

	TextInterpreter textInterpreter(spawner);
	textInterpreter.initializeTextFiles();
	textInterpreter.interpretLevelFile();

	vector <Marble*> marbleVectors = spawner->getMarble();
	Marble* marble = marbleVectors[0];
	vector <Wall*> wallVectors = spawner->getWall();

	Client* gameClient = new Client();
	Vector2f* newPosition = { nullptr };

	//Fixed time loop
	float timeStep = 1.0f / 120.0f;
	int velocityIterations = 8;
	int positionIterations = 3;


	//Basic game loop using polling. Interrupt would be better.
	while (gameClient->getWindow()->isOpen())
	{

		gameWorld->getWorld()->Step(timeStep, velocityIterations, positionIterations);

		gameClient->getWindow()->pollEvent(gameClient->gameEvent);

		if (gameClient->gameEvent.type == Event::Closed)
		{
			if (gameClient->getPeer() != NULL)
			{
				gameClient->disconnectPeer();
			}
			gameClient->getWindow()->close();
		}

		while (enet_host_service(gameClient->getClient(), gameClient->getENetEvent(), 0) > 0)
		{
			switch (gameClient->getENetEvent()->type) 
			{
			case ENET_EVENT_TYPE_RECEIVE:
				cout << "Packet received!\n";
				Vector2f* newPosition = new Vector2f;
				memcpy(newPosition, gameClient->getENetEvent()->packet->data, gameClient->getENetEvent()->packet->dataLength);
				cout << newPosition->x << "," << newPosition->y << "\n";
				//enemy.setPosition(sf::Vector2f(newPosition->x, newPosition->y));
				delete newPosition;
				enet_packet_destroy(gameClient->getENetEvent()->packet);
				break;
			}
		}

		if (gameClient->gameEvent.type == Event::KeyPressed)
		{
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				marble->updateLinearVelocity(b2Vec2(-0.1f, 0.0f));
			}

			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				marble->updateLinearVelocity(b2Vec2(0.1f, 0.0f));
			}
			if (Keyboard::isKeyPressed(Keyboard::Up))
			{
				marble->updateLinearVelocity(b2Vec2(0.0f, 0.1f));
			}
			if (Keyboard::isKeyPressed(Keyboard::Down))
			{
				marble->updateLinearVelocity(b2Vec2(0.0f, -0.1f));
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				gameClient->getWindow()->close();
			}
		}
		else
		{
			marble->updateLinearVelocity(b2Vec2(0.0f, 0.0f));
		}

		marble->updatePosition();

		// Draw the scene!
		gameClient->getWindow()->clear(Color::Black);
		for (int i = 0; i < wallVectors.size(); i++)
		{
			gameClient->getWindow()->draw(wallVectors[i]->getGraphicBody());
		}
		for (int i = 0; i < marbleVectors.size(); i++)
		{
			gameClient->getWindow()->draw(marbleVectors[i]->getMarbleGraphic());
		}
		gameClient->getWindow()->display();
	}

	enet_host_destroy(gameClient->getClient());
	atexit(enet_deinitialize);
}