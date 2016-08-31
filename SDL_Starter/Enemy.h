#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <SDL.h>
#include "Entity.h"

class Enemy : public Entity  {
private:
	bool m_alive;
public:
	void UpdateAI();
	Enemy() {};
	Enemy(float posX, float posY, float width, float height, SDL_Surface* surfacePtr, Renderer* renPtr);
	bool GetAlive();
	void SetAlive(bool isAlive);
};

#endif
