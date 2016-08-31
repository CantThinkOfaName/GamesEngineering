#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Initialise(Renderer * renPtr, bool isThreaded)
{
	m_gameOver = false;
	m_render = renPtr;
	m_isThreaded = isThreaded;
	int ENEMY_PER_ROW = 7;
	int ENEMY_ROWS = 3;

	std::string basepath(SDL_GetBasePath());
	std::string imagePath = basepath + "player.bmp";
	m_playerSur = SDL_LoadBMP(imagePath.c_str());

	imagePath = basepath + "enemy.bmp";
	m_enemySur = SDL_LoadBMP(imagePath.c_str());

	imagePath = basepath + "bullet.bmp";
	m_bulletSur = SDL_LoadBMP(imagePath.c_str());

	for (int i = 0; i < ENEMY_ROWS; i++) {
		for (int j = 0; j < ENEMY_PER_ROW; j++) {
			m_enemies.push_back(new Enemy(50.0f+(100.0f*j), 50.0f + (100.0f*i), 50.0f, 50.0f, m_enemySur, m_render));
		}
	}
	m_player = Player(10.0f, 500.0f, 50.0f, 50.0f, m_playerSur, m_render);
	m_bullet = Bullet(0.0f, 0.0f, 50.0f, 50.0f, m_bulletSur, m_render);
	m_player.SetBulletPtr(&m_bullet);

	imagePath = basepath + "gameOver.bmp";
	m_gameOverSur = SDL_LoadBMP(imagePath.c_str());
	m_gameOverTxt = SDL_CreateTextureFromSurface(m_render->GetRenderer(), m_gameOverSur);

}

void Game::Update(float deltaTime)
{
	for (int i = 0; i < m_enemies.size(); i++) {
		if (m_enemies.at(i)->GetAlive()) {
			
			
				m_enemies.at(i)->UpdateAI();
				m_enemies.at(i)->Update(0.9);
			
			
			if (SDL_HasIntersection(&m_player.GetRect(), &m_enemies.at(i)->GetRect()) == SDL_TRUE) {
				m_gameOver = true;
			}
		}
	}
	m_player.UpdateInput();
	m_player.Update(0.9);
	if (m_bullet.GetShot()) {
		m_bullet.Update(0.9);
		for (int i = 0; i < m_enemies.size(); i++) {
			if (m_enemies.at(i)->GetAlive()){

				if (SDL_HasIntersection(&m_bullet.GetRect(), &m_enemies.at(i)->GetRect()) == SDL_TRUE) {
					messageQueue.push_back("Enemy Shot");
					m_bullet.SetShot(false);
					m_enemies.at(i)->SetAlive(false);
				}
				
			}
		}
	}
	m_hud.Update();
}

void Game::Draw()
{
	m_render->ClearScreen();
	for (int i = 0; i < m_enemies.size(); i++) {
		if (m_enemies.at(i)->GetAlive()) {
			m_render->Draw(m_enemies.at(i)->GetTexture(), &m_enemies.at(i)->GetRect());
		}
	}
	if (!m_gameOver) {
		m_render->Draw(m_player.GetTexture(), &m_player.GetRect());
	}
	
	if (m_bullet.GetShot()) {
		m_render->Draw(m_bullet.GetTexture(), &m_bullet.GetRect());
	}
	if (m_gameOver) {
		m_render->Draw(m_gameOverTxt, &m_gameOverRect);
	}
	SDL_RenderPresent(m_render->GetRenderer());
	m_hud.Draw(m_render);
}

vector<Enemy*> Game::GetEnemies()
{
	return m_enemies;
}

vector<string> Game::GetMessages()
{
	return messageQueue;
}

void Game::ClearMessageQueue()
{
	messageQueue.clear();
}

HUD Game::getHUD()
{
	return m_hud;
}
