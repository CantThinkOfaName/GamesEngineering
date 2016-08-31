
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include "Renderer.h"
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "Game.h"

#include <vector>

using namespace std;
#include <iostream>


bool quit = false;


int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;
SDL_mutex * enemyUpdate_mtx = SDL_CreateMutex();

class ThreadPool {
public:
	void AddTask(void* task, std::string taskName, void* data) {
		if (m_freeWorkers.size() > 0) {
			SDL_Thread* newThread = m_freeWorkers.back();
			m_freeWorkers.pop_back();
			//newThread = SDL_CreateThread(task, taskName, data);
			m_Workers.push_back(newThread);
		}
	};
private:
	std::vector<SDL_Thread*> m_freeWorkers;
	std::vector<SDL_Thread*> m_Workers;
};

class BoundedBuffer {
	SDL_mutex* m_mutex = SDL_CreateMutex();
	SDL_sem* m_notFull_sem;
	SDL_sem* m_notEmpty_sem;
	int count = 0;
	int BUFFER_SIZE = 10;
	std::vector<Enemy*> buffer;

public:
	BoundedBuffer() {
		m_notFull_sem = SDL_CreateSemaphore(0);
		m_notEmpty_sem = SDL_CreateSemaphore(BUFFER_SIZE);
	};

	void Deposit(Enemy* item) {
	
		while (buffer.size() >= BUFFER_SIZE) {
			//std::cout << "Buffer No Longer Full: " << std::endl;
			
			SDL_SemWait(m_notFull_sem);
		}
		if (SDL_LockMutex(m_mutex)==0);
		buffer.push_back(item);
		count++;
		SDL_UnlockMutex(m_mutex);
		SDL_SemPost(m_notEmpty_sem);
		

	}
	Enemy* Retrieve() {
	
		while (buffer.size() == 0) {
			//std::cout << "Buffer No Longer Empty: " << std::endl;
			SDL_SemWait(m_notEmpty_sem);
		}
		if (SDL_LockMutex(m_mutex) == 0);
		buffer.front() = std::move(buffer.back());
		Enemy* newItem = buffer.back();
		buffer.pop_back();
		SDL_UnlockMutex(m_mutex);
		SDL_SemPost(m_notFull_sem);

		return newItem;
	}
	BoundedBuffer(const BoundedBuffer&){}
};
BoundedBuffer enemyBuf = BoundedBuffer();

int EnemyProducer(void* gameData) {
	
	Game* game = static_cast<Game*>(gameData);
	vector<Enemy*> enemiesToProcess = game->GetEnemies();

	while (!quit) {
		for (int i = 0; i < enemiesToProcess.size(); i++) {
			//if ((enemiesToProcess.at(i)->GetIsUpdated())) {
				//if (enemiesToProcess.at(i)->GetRect().x < 0) {
					enemyBuf.Deposit(enemiesToProcess.at(i));
				//}
				//else if (enemiesToProcess.at(i)->GetRect().x + enemiesToProcess.at(i)->GetRect().w > SCREEN_WIDTH) {
					//enemyBuf.Deposit(enemiesToProcess.at(i));
				//}
			//}
			
		}
		

	}
	return 24;
}

int EnemyConsumer(void* gameData) {
	
	
	while (!quit) {
		Enemy* e = enemyBuf.Retrieve();
		if (e != NULL) {
			std::cout << "Consuming: " << std::endl;
			e->UpdateAI();
			e->Update(0.1);
		}
		
	}
	return 24;
}

int Render(void* gameData) {
	Game* game = static_cast<Game*>(gameData);
	game->Draw();
	return 56;
}
SDL_Thread *conThread = NULL; 
SDL_Thread *proThread = NULL;
SDL_Thread *conThreadB = NULL;

int main(int argc, char *argv[]) {

	bool isThreaded = true;

	Game game;
	Renderer r = Renderer();
	game.Initialise(&r, isThreaded);

	

	SDL_Event e;
	if (isThreaded) {
		proThread = SDL_CreateThread(EnemyProducer, "Producer Thread", &game);
		conThread = SDL_CreateThread(EnemyConsumer, "Consumer Thread", &game);
		conThreadB = SDL_CreateThread(EnemyConsumer, "Consumer Thread", &game);
		
	}

	while (!quit){
		
		// Set ENEMY list to update ready?
		
		
		cout << "Game Update" << endl;
		game.Update(0.9);
		game.Draw();
		
		
	}
	
	
	return 0;

}