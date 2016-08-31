#pragma once
#ifndef BULLET_H
#define BULLET_H

#include <iostream>

#include <SDL.h>
#include <SDL_events.h>
#include "Entity.h"

class Bullet : public Entity {
private:
	bool m_shot;
public:
	Bullet() {};
	Bullet(float posX, float posY, float width, float height, SDL_Surface* surfacePtr, Renderer* renPtr);

	void Update(float deltaTime);
	void Fire(float posX, float posY);
	bool GetShot();
	void SetShot(bool isShot);
};

#endif