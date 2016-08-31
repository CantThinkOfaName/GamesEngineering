#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <map>
#include <SDL.h>
#include <SDL_events.h>
#include "Entity.h"
#include "Bullet.h"

class Player : public Entity {
private:
	std::map<std::string, bool> m_input;
	Bullet * m_bulletPtr;
public:
	Player() {};
	Player(float posX, float posY, float width, float height, SDL_Surface* surfacePtr, Renderer* renPtr);
	void SetBulletPtr(Bullet * bltPtr);
	void UpdateInput();
	void Update(float deltaTime);

};

#endif