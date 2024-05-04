#include "Application.h"

Application::Application(float screenWidth, float screenHeight, double deltaTime)
{
    m_bRestart = false;
    m_bQuit = false;
    
    // Initialize the physics world
    m_gravity = b2Vec2(0.0f, 2.0f);
    m_world = new b2World(m_gravity);
    
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
    m_deltaTime = deltaTime;

    // Create the game objects
    m_player = Player(screenWidth, screenHeight, m_world);
    m_ground = Ground(screenWidth * 0.5f, screenHeight - 10, m_world);
    m_ceiling = Ground(screenWidth * 0.5f, 10, m_world);
    m_obstacleQueue = ObstacleQueue(screenWidth, screenHeight, m_world);

    // Setting up the collision listener
    m_collisionListener = CollisionListener(&m_player);
    m_world->SetContactListener(&m_collisionListener);

    // Create a window
    m_window = SDL_CreateWindow("Minidemo",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        m_screenWidth, m_screenHeight,
        0);

    // If the window failed to be created
    if (!m_window)
    {
        std::cout << "Failed to create window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }

    m_windowSurface = SDL_GetWindowSurface(m_window);

    // If the surface failed to be created
    if (!m_windowSurface)
    {
        std::cout << "Failed to get the surface from the window\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return;
    }

    //if (TTF_Init() == -1)
    //{
    //    std::cout << "Unable to initialize SDL_ttf\n";
    //    std::cout << "TTF Error: " << TTF_GetError() << "\n";
    //    return;
    //}

    //font = TTF_OpenFont("font.ttf", 24); // Adjust the size (24 here) as needed
    //if (!font)
    //{
    //    std::cout << "Unable to load font\n";
    //    std::cout << "TTF Error: " << TTF_GetError() << "\n";
    //    return;
    //}
}

Application::~Application()
{
    delete m_world;
    SDL_FreeSurface(m_windowSurface);
    SDL_DestroyWindow(m_window);
}

void Application::Loop()
{
    // Game loop
    bool quit = false;
    while (!quit)
    {

        // See if events needs to be processed
        while (SDL_PollEvent(&m_windowEvent) > 0)
        {
            m_player.HandleInput(m_windowEvent);
            // If the event is the quit event
            if (m_windowEvent.type == SDL_QUIT)
            {
                quit = true;
                m_bQuit = true;
            }
        }

        UpdateWorld(m_deltaTime);

        // Check for collisions and handle reset
        if (m_player.IsCollisionOccured())
        {
            m_bRestart = true;
            break;
        }

        DrawWorld();
    }
}

void Application::UpdateWorld(double deltaTime)
{
    m_world->Step(deltaTime, 6, 2); // velocity iterations, position iterations
    
    m_player.Update(deltaTime);
    m_obstacleQueue.Update(deltaTime);
}

void Application::DrawWorld()
{
    SDL_FillRect(m_windowSurface, NULL, SDL_MapRGB(m_windowSurface->format, 0, 0, 0)); // Clear the screen to black
    m_player.Draw(m_windowSurface); // Draw the player
    m_obstacleQueue.Draw(m_windowSurface); // Draw the obstacles
    m_ground.Draw(m_windowSurface); // Draw the ground
    m_ceiling.Draw(m_windowSurface); // Draw the ceiling
    SDL_UpdateWindowSurface(m_window); // Update the window
}
