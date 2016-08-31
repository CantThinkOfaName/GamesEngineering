#include "Entity.h"

Entity::Entity(float posX, float posY, float width, float height, SDL_Surface * surfacePtr, Renderer* renPtr)
{
	m_positionX = posX;
	m_positionY = posY;
	m_rect = { (int)m_positionX, (int)m_positionY, (int)width, (int)height };
	m_surface = surfacePtr;

	m_texture = SDL_CreateTextureFromSurface(renPtr->GetRenderer(), surfacePtr);
	m_renPtr = renPtr;
	m_velocityX = 0;
	m_velocityY = 0;
	
}

Entity::~Entity()
{
	
}

void Entity::Update(float deltaTime)
{
	m_positionX += m_velocityX * deltaTime;
	m_positionY += m_velocityY * deltaTime;

	m_rect.x = m_positionX;
	m_rect.y = m_positionY;
	
}

SDL_Surface * Entity::GetSurface()
{
	return m_surface;
}

SDL_Rect Entity::GetRect()
{
	return m_rect;
}

SDL_Texture* Entity::GetTexture()
{
	return m_texture;
}

float Entity::GetPositionX()
{
	return m_positionX;
}

void Entity::Render()
{
	//m_renPtr->RenderCopy();
}

bool Entity::GetIsUpdated()
{
	return m_updated;
}
