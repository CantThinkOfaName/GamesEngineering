#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <SDL.h>
#include "Renderer.h"

class Entity {
protected:
	SDL_Surface *m_surface;
	SDL_Rect m_rect;
	Renderer * m_renPtr;
	SDL_Texture* m_texture;
	std::string m_File;
	float m_positionX;
	float m_positionY;
	float m_velocityX;
	float m_velocityY;
	bool m_updated;
	
public:
	Entity() {};
	Entity(float posX, float posY, float width, float height, SDL_Surface* surfacePtr, Renderer* renPtr);
	~Entity();
	virtual void Update(float deltaTime);

	SDL_Surface * GetSurface();
	SDL_Rect GetRect();
	SDL_Texture * GetTexture();
	float GetPositionX();
	void Render();
	bool GetIsUpdated();
};

#endif