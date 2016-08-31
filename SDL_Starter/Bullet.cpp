#include "Bullet.h"

Bullet::Bullet(float posX, float posY, float width, float height, SDL_Surface * surfacePtr, Renderer * renPtr)
	: Entity(posX, posY, width, height, surfacePtr, renPtr)
{
	m_shot = false;
}

void Bullet::Update(float deltaTime)
{
	if (m_shot) {
		Entity::Update(deltaTime);
	}
	if (m_positionY + m_rect.h < 0) {
		m_shot = false;
	}
}

void Bullet::Fire(float posX, float posY)
{
	m_positionX = posX;
	m_positionY = posY;
	m_shot = true;
	m_velocityY = -10;
}

bool Bullet::GetShot()
{
	return m_shot;
}

void Bullet::SetShot(bool isShot)
{
	m_shot = isShot;
}
