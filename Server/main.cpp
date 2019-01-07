#include <iostream>
#include <SFML/Graphics.hpp>
#include <enet/enet.h>

using namespace std;
using namespace sf;

void main()
{
	RenderWindow window(VideoMode(800, 600), "Server Window");
	Event e;
	
	RectangleShape background;
	background.setSize(Vector2f(800, 600));
	background.setPosition(0.0f, 0.0f);


	Vector2f position;
	position = Vector2f(0.0f, 0.05f);
	int counter = 0;

	if (enet_initialize() != 0)
	{
		cout << "Enet failed to initialise!" << "\n\n";
	}

	ENetAddress address;
	ENetHost* server;
	ENetEvent enetEvent;

	ENetPacket* dataPacket;

	address.host = ENET_HOST_ANY;
	address.port = 1234;

	server = enet_host_create(&address, 32, 2, 0, 0);

	if (server == NULL)
	{
		cout << "Server failed to initialise!" << "\n\n";
	}

	while (window.isOpen())
	{
		window.pollEvent(e);

		if (e.type == Event::Closed) {
			window.close();

		}

		while (enet_host_service(server, &enetEvent, 1000) > 0)
		{
			switch (enetEvent.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				
				cout << "A client connected from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << ".\n";
				enetEvent.peer->data = "This is a client";

				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				cout << "The client from address " << enetEvent.peer->address.host << ":" << enetEvent.peer->address.port << " disconnected \n";
				
				enetEvent.peer->data = NULL;
				
				break;
			}
		}

		if (counter <= 2)
		{
			position.y = -0.05f;
		}

		else if (counter <= 3)
		{
			position.y = 0.05f;
		}
		else { counter = 0; }
		
		counter++;

		
		if (e.type == Event::KeyPressed)
		{

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				enet_peer_disconnect(enetEvent.peer, 0);
				//Force the disconnect after being gentle
				enet_peer_reset(enetEvent.peer);
				window.close();
			}
		}

		else
		{
			cout << "The position of the entity is moving: (" << position.x << "," << position.y << ")\n";
			dataPacket = enet_packet_create(&position, sizeof(Vector2f), ENET_PACKET_FLAG_RELIABLE);
			enet_host_broadcast(server, 0, dataPacket);
			
		}

		window.clear(Color::Blue);
		window.display();
	}

	enet_host_destroy(server);
	atexit(enet_deinitialize);
}