#pragma once
#ifndef GAME_H
#define GAME_H


#include <SDL.h>
#include <SDL_image.h>
#include "Renderer.h"
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"

using namespace std;
#include <iostream>
#include <vector>
class Game {
private:
	Renderer *m_render;
	Player m_player;
	Bullet m_bullet;
	vector<Enemy*> m_enemies;
	SDL_Surface* m_playerSur;
	SDL_Surface* m_enemySur;
	SDL_Surface* m_bulletSur;
	SDL_Surface* m_gameOverSur;
	SDL_Rect m_gameOverRect = { 0,0, 800, 600 };
	SDL_Texture* m_gameOverTxt;
	bool m_isThreaded;
	bool m_gameOver;
public:
	Game();
	~Game();
	void Initialise(Renderer* renPtr, bool isThreaded);
	void Update(float deltaTime);
	void Draw();
	vector<Enemy*> GetEnemies();
};

#endif