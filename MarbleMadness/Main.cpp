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
#include "Spawner.h"
#include "World.h"
#include "TextInterpreter.h"
#include "Client.h"
#include "MyContactListener.h"
#include "TextDraw.h"

using namespace std;
using namespace sf;

void main()
{
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

	MyContactListener myContactListenerInstance;
	gameWorld->getWorld()->SetContactListener(&myContactListenerInstance);

	float score = 0;
	TextDraw text;
	bool levelChecker = false;

	//Fixed time loop
	float timeStep = 1.0f / 120.0f;
	int velocityIterations = 8;
	int positionIterations = 3;


	//Basic game loop using polling. Interrupt would be better.
	while (gameClient->getWindow()->isOpen())
	{
		// With how much this is just calling functions from the game client, would be better to move all of this into the game client itself...
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
			newPosition = new Vector2f;
			switch (gameClient->getENetEvent()->type) 
			{
			case ENET_EVENT_TYPE_RECEIVE:
				cout << "Packet received!\n";
				memcpy(newPosition, gameClient->getENetEvent()->packet->data, gameClient->getENetEvent()->packet->dataLength);
				cout << newPosition->x << "," << newPosition->y << "\n";
				
				for (int i = 1; i < marbleVectors.size(); i++)
				{
					marbleVectors[i]->updateLinearVelocity(b2Vec2(newPosition->x, newPosition->y));
				}

				enet_packet_destroy(gameClient->getENetEvent()->packet);
				break;

			case ENET_EVENT_TYPE_NONE:
				break;

			case ENET_EVENT_TYPE_CONNECT:
				cout << "Connected to server: " << gameClient->getENetEvent()->peer->address.host << ":" << gameClient->getENetEvent()->peer->address.port << ".\n";
				break;

			case ENET_EVENT_TYPE_DISCONNECT:
				cout << "The server " << gameClient->getENetEvent()->peer->address.host << ":" << gameClient->getENetEvent()->peer->address.port << " disconnected \n";
				gameClient->getENetEvent()->peer->data = NULL;
				break;
			}
			delete newPosition;
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

			// Press Space will create the new level
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				// Check if there are more levels to be loaded, so we don't crash...
				levelChecker = textInterpreter.levelsCheck();
				
				if (levelChecker)
				{
					//First we delete the all of the objects in the wall and marble vectors
					spawner->deleteVectors();

					while (wallVectors.size() != 0)
					{
						wallVectors.pop_back();
					}
					while (marbleVectors.size() != 0)
					{
						marbleVectors.pop_back();
					}
					
					// Load in the new text file
					textInterpreter.interpretLevelFile();

					marbleVectors = spawner->getMarble();
					marble = marbleVectors[0];
					wallVectors = spawner->getWall();
					score = 0;
				}
				else
				{
					gameClient->getWindow()->close();
				}
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

		// Draw the scene!
		gameClient->getWindow()->clear(Color::Black);
		for (int i = 0; i < wallVectors.size(); i++)
		{
			gameClient->getWindow()->draw(wallVectors[i]->getGraphicBody());
		}
		for (int i = 0; i < marbleVectors.size(); i++)
		{
			marbleVectors[i]->updatePosition();
			gameClient->getWindow()->draw(marbleVectors[i]->getMarbleGraphic());
		}
		
		if (marbleVectors[0]->getNumContacts() > 0)
		{
			score++;
			cout << int(score / 100) << endl;
			text.setString(to_string(int(score / 120)));
		}
		gameClient->getWindow()->draw(text.getText());
		gameClient->getWindow()->display();
	}

	enet_host_destroy(gameClient->getClient());
	atexit(enet_deinitialize);

	delete gameWorld;
}