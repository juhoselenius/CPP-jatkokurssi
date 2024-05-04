#pragma once

#include <SDL.h>
#include <Box2D.h>

/*!
* @brief Represents the player class.
*
* The Player class handles player interaction logic (inputs etc.).
*/
class Player
{
public:
	/*! Default constructor of a player.
	 */
	Player() = default;

	/*! Constructs a Player object with specified parameters.
	 *
	 * @param screenWidth The width of the screen.
	 * @param screenHeight The height of the screen.
	 * @param gameWorld The Box2D physics world.
	 */
	Player(float screenWidth, float screenHeight, b2World* gameWorld);

	/*! Default destructor of a player.
	 */
	~Player() = default;

	/*! Handles input events.
	*
	* @param event The SDL event to handle.
	*/
	void HandleInput(SDL_Event const &event);

	/*! Updates the player's state based on elapsed time.
	 *
	 * @param deltaTime The time elapsed since the last frame.
	 */
	void Update(double deltaTime);

	/*! Draws the player on the screen.
	 *
	 * @param windowSurface The surface of the SDL window.
	 */
	void Draw(SDL_Surface* windowSurface);

	/*! Handles collision events involving the player. */
	void HandleCollision();

	/*! Checks if a collision with the player has occurred.
	 *
	 * @return True if a collision occurred, otherwise false.
	 */
	bool IsCollisionOccured();

	b2BodyDef m_playerBodyDef; //!< The Box2D body definition for the player.

private:
	SDL_Surface* m_image; //!< The image representing the player.
	SDL_Rect m_imagePosition; //!< The position of the player image on the screen.

	int m_playerImageWidth = 60; //!< The width of the player image.
	int m_playerImageHeight = 54; //!< The height of the player image.

	int m_playerJumpStrength = -15; //!< The strength of the player's jump.

	b2World* m_world; //!< The Box2D physics world.

	//Physics
	b2Body* m_playerBody; //!< The Box2D body for the player.
	b2PolygonShape m_playerShape; //!< The shape of the player's body.
	b2FixtureDef m_playerFixtureDef; //!< The fixture definition for the player's body.

	float m_initialPlayerPositionX; //!< The initial x-coordinate of the player.
	float m_initialPlayerPositionY; //!< The initial y-coordinate of the player.

	bool m_collisionOccured; //!< Flag indicating if a collision has occurred.
};