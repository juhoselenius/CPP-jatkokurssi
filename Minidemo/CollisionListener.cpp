#include "CollisionListener.h"
#include <string>

CollisionListener::CollisionListener(Player* player)
{
	m_player = player;
}

void CollisionListener::BeginContact(b2Contact* contact)
{
	// Get the two bodies involved in the collision
	b2FixtureUserData userDataA = contact->GetFixtureA()->GetUserData();
    b2FixtureUserData userDataB = contact->GetFixtureB()->GetUserData();

    // Check if the player collided with anything
    if (userDataA.pointer == m_player->m_playerBodyDef.userData.pointer ||
        userDataB.pointer == m_player->m_playerBodyDef.userData.pointer)
    {
       m_player->HandleCollision();
    }
}
