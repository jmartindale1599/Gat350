#include "ContactListener.h"

#include "FrameWork/Actor.h"

#include "Components/CollisionComponent.h"

#include <iostream>

namespace neu {

	void ContactListener::BeginContact(b2Contact* contact) {

		b2Fixture* fixtureA = contact->GetFixtureA();

		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer) {

			Actor* actorA = (Actor*)(fixtureA->GetUserData().pointer);

			Actor* actorB = (Actor*)(fixtureB->GetUserData().pointer);

			if (actorA->isDestroyed() || actorB->isDestroyed()) return;

			if (actorA->GetComponent<CollisionComponent>()){

			actorA->GetComponent<CollisionComponent>()->onCollisionEnter(actorB);

			}

			if (actorB->GetComponent<CollisionComponent>()) {

				actorB->GetComponent<CollisionComponent>()->onCollisionEnter(actorA);

			}

		}

	}

	void ContactListener::EndContact(b2Contact* contact) {

		b2Fixture* fixtureA = contact->GetFixtureA();

		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer) {

			Actor* actorA = (Actor*)(fixtureA->GetUserData().pointer);

			Actor* actorB = (Actor*)(fixtureB->GetUserData().pointer);

			if (actorA->isDestroyed() || actorB->isDestroyed()) return;

			if (actorA->GetComponent<CollisionComponent>()) {

				actorA->GetComponent<CollisionComponent>()->onCollisionExit(actorB);

			}

			if (actorB->GetComponent<CollisionComponent>()) {

				actorB->GetComponent<CollisionComponent>()->onCollisionExit(actorA);

			}

		}

	}

}
