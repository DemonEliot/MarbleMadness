#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <enet\enet.h>

using namespace std;
using namespace sf;

class Client 
{
public:
	Client() {

		window = new RenderWindow(VideoMode(1920, 1080), "Game Window");

		if (enet_initialize() != 0)
		{
			cout << "Enet failed to initialise!" << "\n\n";
		}

		createHost();
		setHostAddress();
		connectHost();

	};

	void createHost()
	{
		client = enet_host_create(NULL, 1, 2, 0, 0);

		if (client == NULL)
		{
			cout << "Client failed to initialise!" << "\n\n";
		}
	}

	void setHostAddress()
	{
		enet_address_set_host(&address, "localhost");
		address.port = 1234;
	}

	void connectHost()
	{
		peer = enet_host_connect(client, &address, 2, 0);

		if (peer == NULL) {
			cout << "No available peers for initializing an ENet connection.\n";
		}
	}

	ENetPeer* getPeer()
	{
		return peer;
	}

	void disconnectPeer()
	{
		enet_peer_disconnect_now(peer, 0);
	}

	RenderWindow* getWindow()
	{
		return window;
	}

	ENetHost* getClient()
	{
		return client;
	}

	ENetEvent* getENetEvent()
	{
		return &enetEvent;
	}

	Event gameEvent;

private:
	ENetAddress address;
	ENetHost* client;
	ENetPeer* peer;
	ENetEvent enetEvent;

	RenderWindow* window;
};