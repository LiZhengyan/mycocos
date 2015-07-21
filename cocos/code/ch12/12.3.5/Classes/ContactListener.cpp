//
//  ContactListener.cpp
//  HelloBox2D
//
//  Created by tonyguan on 13-10-24.
//  Copyright (c) 2013年 tonyguan. All rights reserved.
//

#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* contact)
{
	log("BeginContact");

	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	auto spriteA = (Sprite*)bodyA->GetUserData();
	auto spriteB = (Sprite*)bodyB->GetUserData();
	
	if (spriteA != NULL && spriteB != NULL)
	{
        spriteA->setColor(Color3B::YELLOW);
        spriteB->setColor(Color3B::YELLOW);
	}
}

void ContactListener::EndContact(b2Contact* contact)
{
	log("EndContact");

	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	auto spriteA = (Sprite*)bodyA->GetUserData();
	auto spriteB = (Sprite*)bodyB->GetUserData();
	
	if (spriteA != NULL && spriteB != NULL)
	{
        spriteA->setColor(Color3B::WHITE);
        spriteB->setColor(Color3B::WHITE);
	}
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	log("PreSolve");
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	log("PostSolve");
}