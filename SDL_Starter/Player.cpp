#include "Player.h"

Player::Player(float posX, float posY, float width, float height, SDL_Surface * surfacePtr, Renderer * renPtr)
	: Entity(posX, posY, width, height, surfacePtr, renPtr)
{
	m_input["left"] = false;
	m_input["right"] = false;
	m_input["fire"] = false;
}

void Player::SetBulletPtr(Bullet * bltPtr)
{
	m_bulletPtr = bltPtr;
}

void Player::UpdateInput()
{
	

	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		
		
		if (event.type == SDL_KEYDOWN)
		{
			//Select surfaces based on key press
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				m_input["left"] = true;
				break;
			case SDLK_d:
				m_input["right"] = true;
				break;
			case SDLK_SPACE:
				m_input["fire"] = true;
				break;
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				m_input["left"] = false;
				break;
			case SDLK_d:
				m_input["right"] = false;
				break;
			case SDLK_SPACE:
				m_input["fire"] = false;
				break;
			}
		}
	}

}

void Player::Update(float deltaTime)
{
	m_velocityX = 0;
	if (m_input["left"]) {
		m_velocityX = -5;
	}
	else if (m_input["right"]) {
		m_velocityX = 5;
	}
	if (m_input["fire"]) {
		if (!m_bulletPtr->GetShot()) {
			m_bulletPtr->Fire(m_positionX, m_positionY);
		}
	}
	
	Entity::Update(deltaTime);
}


