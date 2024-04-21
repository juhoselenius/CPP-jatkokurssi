#include <Box2D.h>
#include <SDL.h>
#include <iostream>

b2World* world;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const float BOX_WIDTH = 40.0f;
const float BOX_HEIGHT = 40.0f;

const float BOX_START_X = 320.0f;
const float BOX_START_Y = 1.0f;

const double deltaTime = 1.0 / 60.0;

int main(int argc, char** argv)
{
    // Try to initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Miniprojekti4",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        680, 480,
        0);

    // If the window failed to be created
    if (!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    // Get the surface of the window
    SDL_Surface* window_surface = SDL_GetWindowSurface(window);

    // If the surface failed to be created
    if (!window_surface)
    {
        std::cout << "Failed to get the surface from the window\n";
        return -1;
    }

    // Define the gravity vector.
    b2Vec2 gravity(0.0f, 9.81f);

    // Construct a world object, which will hold and simulate the rigid bodies.
    world = new b2World(gravity);

    //// Ground

    // Define the ground body.
    SDL_Rect groundRect;
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 400.0f);
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;
    groundBox.SetAsBox(SCREEN_WIDTH, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Setting up the visual representation of the ground
    groundRect.x = 0;
    groundRect.y = 400 + (10 / 2);
    groundRect.w = SCREEN_WIDTH + 100;
    groundRect.h = 10;

    //// Box

    // Setting up the box sprite
    SDL_Surface* boxSprite = SDL_LoadBMP("Box.bmp");

    // If the image failed to load
    if (!boxSprite)
    {
        std::cout << "Failed to load image\n";
        std::cout << "SDL2 Error: " << SDL_GetError() << "\n";
        return -1;
    }

    // Define the dynamic body. We set its position and call the body factory.
    SDL_Rect box;
    b2BodyDef boxBodyDef;
    boxBodyDef.type = b2_dynamicBody;
    boxBodyDef.position.Set(BOX_START_X, BOX_START_Y);
    boxBodyDef.fixedRotation = false;
    b2Body* boxBody = world->CreateBody(&boxBodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(BOX_WIDTH / 2, BOX_HEIGHT / 2);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Override the default restitution.
    fixtureDef.restitution = 0.5f;

    // Add the shape to the body.
    boxBody->CreateFixture(&fixtureDef);

    // Setting up the visual representation of the box
    box.x = 0;
    box.y = 0;
    box.w = (int)BOX_WIDTH;
    box.h = (int)BOX_HEIGHT;

    double image_x = 0;
    double image_y = 0;

    // Prepare the simulation
    int velocityIterations = 6;
    int positionIterations = 2;

    // Game loop
    bool quit = false;
    while (!quit)
    {
        // Create an event and see if it needs to be processed
        SDL_Event event;
        while (SDL_PollEvent(&event) > 0)
        {
            // If the event is the quit event
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        // Update the box position and rotation
        b2Vec2 boxPosition = boxBody->GetPosition();
        float boxAngle = boxBody->GetAngle();
        boxAngle *= 180 / b2_pi; // Convert to degrees
        box.x = (int)boxPosition.x;
        box.y = (int)boxPosition.y;


        // Draw into the window
        SDL_FillRect(window_surface, NULL, SDL_MapRGB(window_surface->format, 0, 0, 0)); // Clear the window with black color
        SDL_FillRect(window_surface, &groundRect, SDL_MapRGB(window_surface->format, 0, 255, 0)); // Draw the ground with green color
        SDL_BlitSurface(boxSprite, NULL, window_surface, &box); // Draw the box

        SDL_UpdateWindowSurface(window);
        world->Step(deltaTime, velocityIterations, positionIterations);
    }

    // box2D delete whole world and free memory
    delete world;

    SDL_FreeSurface(window_surface);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}