#include "Enemy.h"

void Enemy::UpdateAI()
{
	if (m_rect.x < 0) {
		m_velocityX = -m_velocityX;
		m_positionX = 10;
		m_positionY += m_rect.h;
	}
	else if (m_rect.x + m_rect.w > m_renPtr->GetScreenWidth()) {
		m_velocityX = -m_velocityX;
		m_positionX = m_renPtr->GetScreenWidth() - m_rect.w-5;
		m_positionY += m_rect.h;

	}
	
	//Entity::Update(0.2);
}

Enemy::Enemy(float posX, float posY, float width, float height, SDL_Surface * surfacePtr, Renderer * renPtr):
	Entity(posX, posY, width, height, surfacePtr, renPtr)
{
	m_velocityX = 5;
	m_alive = true;
}

bool Enemy::GetAlive()
{
	return m_alive;
}

void Enemy::SetAlive(bool isAlive)
{
	m_alive = isAlive;
}
