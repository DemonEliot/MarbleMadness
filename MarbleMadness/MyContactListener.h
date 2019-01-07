#pragma once

#include <Box2D/Box2D.h>
#include "Marble.h"

class MyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) {

		//check if fixture A was a ball
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (bodyUserData)
			static_cast<Marble*>(bodyUserData)->startContact();

		//check if fixture B was a ball
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData)
			static_cast<Marble*>(bodyUserData)->startContact();

	}

	void EndContact(b2Contact* contact) {

		//check if fixture A was a ball
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (bodyUserData)
			static_cast<Marble*>(bodyUserData)->endContact();

		//check if fixture B was a ball
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData)
			static_cast<Marble*>(bodyUserData)->endContact();

	}
};