#pragma once

#include <SDL.h>
#include <Box2D.h>

/*!
 * @brief Represents the obstacle class.
 *
 * The Obstacle class represents the obstacles that the player must avoid in the game.
 */
class Obstacle
{
public:
	/*! Default constructor of an obstacle object. */
	Obstacle() = default;

	/*! Constructs an Obstacle object with specified parameters.
	 *
	 * @param positionX The x-coordinate of the obstacle.
	 * @param positionY The y-coordinate of the obstacle.
	 * @param gameWorld The Box2D physics world.
	 */
	Obstacle(float positionX, float positionY, b2World* gameWorld);

	/*! Default destructor of an obstacle object. */
	~Obstacle() = default;

	/*! Updates the obstacle's state based on elapsed time.
	 *
	 * @param deltaTime The time elapsed since the last frame.
	 */
	void Update(double deltaTime);

	/*! Draws the obstacle on the screen.
	 *
	 * @param windowSurface The surface of the SDL window.
	 */
	void Draw(SDL_Surface* windowSurface);

	double m_upperX; //!< The x-coordinate of the upper obstacle.
	double m_lowerX; //!< The x-coordinate of the lower obstacle;

private:
	b2World* m_world;  //!< The Box2D physics world.
	double m_speed = 8; //!< The speed of the obstacle. 
	
	SDL_Rect m_upperObstacleRect; //!< The rectangle representing the upper part of the obstacle. Visual representation of the obstacle
	b2BodyDef m_upperObstacleBodyDef; //!< The Box2D body definition for the lower part of the obstacle. Physical representation of the upper obstacle
	b2Body* m_upperObstacleBody; //!< The Box2D body for the lower part of the obstacle. Physical representation of the upper obstacle
	b2PolygonShape m_upperObstacleShape; //!< The shape of the lower part of the obstacle. Physical representation of the upper obstacle
	b2FixtureDef m_upperObstacleFixtureDef; //!< The fixture definition for the lower part of the obstacle. Physical representation of the upper obstacle

	SDL_Rect m_lowerObstacleRect; //!< The rectangle representing the lower part of the obstacle. Visual representation of the obstacle
	b2BodyDef m_lowerObstacleBodyDef; //!< The Box2D body definition for the lower part of the obstacle. Physical representation of the lower obstacle
	b2Body* m_lowerObstacleBody; //!< The Box2D body for the lower part of the obstacle. Physical representation of the lower obstacle
	b2PolygonShape m_lowerObstacleShape; //!< The shape of the lower part of the obstacle. Physical representation of the lower obstacle
	b2FixtureDef m_lowerObstacleFixtureDef; //!< The fixture definition for the lower part of the obstacle. Physical representation of the lower obstacle

	float m_obstacleWidth = 40; //!< The width of the obstacle.
	float m_obstacleHeight = 500; //!< The height of the obstacle.

	int gapHalfHeight = 60; //!< The half height of the gap between the upper and lower obstacles.
};

