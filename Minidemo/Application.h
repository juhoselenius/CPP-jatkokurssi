#pragma once

#include <SDL.h>
#include <iostream>
#include <Box2D.h>
#include "Ground.h"
#include "ObstacleQueue.h"
#include "CollisionListener.h"
//#include <SDL_ttf.h>

/*!
 * @brief Represents the main application class.
 *
 * The Application class manages the main loop of the application and handles game logic.
 */
class Application
{
public:
	/*!
	 * @brief Constructs an Application object with specified parameters.
	 *
	 * @param screenWidth The width of the screen.
	 * @param screenHeight The height of the screen.
	 * @param deltaTime The time interval between each frame.
	 */
	Application(float screenWidth, float screenHeight, double deltaTime);
	/*!
	 * @brief Destructor of the Application object.
	 */
	~Application();

	/*!
	* @brief Updates the game world.
	*
	* @param deltaTime The time interval between each frame.
	*/
	void UpdateWorld(double deltaTime);
	/*!
	 * @brief Draws the game world.
	 */
	void DrawWorld();
	/*!
	 * @brief Runs the main loop of the application.
	 */
	void Loop();

	// Physics
	b2World* m_world; //!< The Box2D physics world.
	b2Vec2 m_gravity; //!< The gravity vector.

	Player m_player; //!< The player object.

	bool m_bRestart; //!< Flag indicating whether the game should be restarted.
	bool m_bQuit; //!< Flag indicating whether the application should quit.

	//TTF_Font* font; //!< The TrueType font used for rendering.

private:
	float m_screenWidth; //!< The width of the screen.
	float m_screenHeight; //!< The height of the screen.
	double m_deltaTime; //!< The time interval between each frame.
	
	SDL_Window* m_window; //!< The SDL window.
	SDL_Surface* m_windowSurface; //!< The surface of the SDL window.
	SDL_Event m_windowEvent; //!< The SDL event.

	Ground m_ground; //!< The ground object.
	Ground m_ceiling; //!< The ceiling object.
	//Obstacle m_obstacle; //!< The obstacle object.
	ObstacleQueue m_obstacleQueue; //!< The obstacle queue.

	CollisionListener m_collisionListener; //!< The collision listener.
};