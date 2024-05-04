#pragma once

#include <deque>
#include "Obstacle.h"

/*! \brief A class to manage the obstacles in the game.
 * 
 * This class is responsible for spawning, updating, drawing and resetting the obstacles in the game.
 */
class ObstacleQueue
{
public:
	/*! Default constructor of an obstacle queue object. */
	ObstacleQueue() = default;

	/*! Constructs an ObstacleQueue object with specified parameters.
		 *
		 * @param screenWidth The width of the screen.
		 * @param screenHeight The height of the screen.
		 * @param gameWorld The Box2D physics world.
		 */
	ObstacleQueue(float screenWidth, float screenHeight, b2World* gameWorld);

	/*! Default destructor of an obstacle queue object. */
	~ObstacleQueue() = default;

	/*! Spawns a new obstacle and adds it to the queue. */
	void SpawnObstacle();

	/*! Updates the obstacle queue based on elapsed time.
	 *
	 * @param deltaTime The time elapsed since the last frame.
	 */
	void Update(double deltaTime);

	/*! Draws all obstacles in the queue on the screen.
	 *
	 * @param windowSurface The surface of the SDL window.
	 */
	void Draw(SDL_Surface* windowSurface);

	/*! Resets the obstacle queue to its initial state. */
	void Reset();

	float m_lastSpawnTime = 0.0f; //!< The time when the last obstacle was spawned.
	int m_spawnInterval = 2000; //!< The interval between each obstacle spawn.

private:
	b2World* m_world; //!< The Box2D physics world.
	int m_screenWidth; //!< The width of the screen.
	int m_screenHeight; //!< The height of the screen.
	
	std::deque<Obstacle> m_obstacleQueue; //!< The queue of obstacles.

	Uint32 m_currentTime; //!< The current time.
};