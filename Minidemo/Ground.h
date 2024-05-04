#pragma once

#include <SDL.h>
#include <Box2D.h>

/*!
* @brief Represents the ground class.
*
* The Player class represents the ground blocks that act as the top and bottom barriers of the game area.
*/
class Ground
{
public:
	/*! Default constructor of a ground object. */
	Ground() = default;

	/*! Constructs a Ground object with specified parameters.
	*
	* @param positionX The x-coordinate of the ground.
	* @param positionY The y-coordinate of the ground.
	* @param gameWorld The Box2D physics world.
	*/
	Ground(float positionX, float positionY, b2World* gameWorld);

	/*! Default destructor of a ground object. */
	~Ground() = default;

	/*! Draws the ground on the screen.
	 *
	 * @param windowSurface The surface of the SDL window.
	 */
	void Draw(SDL_Surface* windowSurface);

private:
	SDL_Rect m_groundRect; //!< The rectangle representing the ground.
	b2BodyDef m_groundBodyDef; //!< The Box2D body definition for the ground.
	b2Body* m_groundBody; //!< The Box2D body for the ground.
	b2PolygonShape m_groundShape; //!< The shape of the ground.
	b2FixtureDef m_groundFixtureDef; //!< The fixture definition for the ground.

	float m_groundWidth = 480; //!< The width of the ground.
	float m_groundHeight = 40; //!< The height of the ground.
};