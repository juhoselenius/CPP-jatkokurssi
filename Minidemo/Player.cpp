#include "Player.h"
#include <iostream>
#include <cmath>
#include "Application.h"

Player::Player(float screenWidth, float screenHeight, b2World* gameWorld)
{
    m_world = gameWorld;
    m_collisionOccured = false;

    m_initialPlayerPositionX = screenWidth / 6;
    m_initialPlayerPositionY = screenHeight / 5;

    // Physics
    //// Define the dynamic body
    m_playerBodyDef.type = b2_dynamicBody;
    m_playerBodyDef.position = b2Vec2(m_initialPlayerPositionX, m_initialPlayerPositionY);
    m_playerBodyDef.fixedRotation = false;
    m_playerBody = m_world->CreateBody(&m_playerBodyDef);

    //// Define the shape of the body
    m_playerShape.SetAsBox(m_playerImageWidth * 0.5f, m_playerImageHeight * 0.5f);

    //// Define the fixture of the body
    m_playerFixtureDef.shape = &m_playerShape;
    m_playerFixtureDef.density = 1.0f;
    m_playerFixtureDef.friction = 0.3f;
    m_playerFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_playerBody->CreateFixture(&m_playerFixtureDef);
    
    m_image = SDL_LoadBMP("sprites/Ghroth_10.bmp");
    
    m_imagePosition.x = m_initialPlayerPositionX - m_playerImageWidth * 0.5f;
    m_imagePosition.y = m_initialPlayerPositionY - m_playerImageHeight * 0.5f;
    m_imagePosition.w = m_playerImageWidth;
    m_imagePosition.h = m_playerImageHeight;
}

void Player::HandleInput(SDL_Event const& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        // Make the player jump
        b2Vec2 velocity = m_playerBody->GetLinearVelocity();
        velocity.y = m_playerJumpStrength;
        m_playerBody->SetLinearVelocity(velocity);
	}
}

void Player::Update(double deltaTime)
{
    // Update the player's position
    b2Vec2 position = m_playerBody->GetPosition();

    m_imagePosition.x = position.x - (m_imagePosition.w * 0.5f);
    m_imagePosition.y = position.y - (m_imagePosition.h * 0.5f);
}

void Player::Draw(SDL_Surface* windowSurface)
{
    SDL_BlitSurface(m_image, nullptr, windowSurface, &m_imagePosition);
}

void Player::HandleCollision()
{
    std::cout << "Player collided!" << std::endl;
    m_collisionOccured = true;
}

bool Player::IsCollisionOccured()
{
    return m_collisionOccured;
}
