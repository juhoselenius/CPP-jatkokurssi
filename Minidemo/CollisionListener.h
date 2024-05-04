#pragma once

#include <Box2D.h>
#include "Player.h"

/*!
 * @brief Represents a collision listener class.
 *
 * The CollisionListener class listens for collision events in the Box2D physics world.
 */
class CollisionListener : public b2ContactListener
{
public:
	/*! Default constructor of a collision listener. */
	CollisionListener() = default;

	/*! Constructs a CollisionListener object with specified parameters.
	*
	* @param player The player object.
	*/
	CollisionListener(Player* player);

	/*! Default destructor of a collision listener. */
	~CollisionListener() = default;

	/*! Handles the begin contact event.
	*
	* @param contact The contact event.
	*/
	void BeginContact(b2Contact* contact) override;

private:
	Player* m_player; //!< The player object.
};