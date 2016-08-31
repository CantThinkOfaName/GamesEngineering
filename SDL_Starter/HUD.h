#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Renderer.h"

using namespace std;
#include <iostream>
#include <vector>
#include <string>

struct Message {
	string data;
	float lifeTimer;
	Message(string messageData, float timer){
		data = messageData;
		lifeTimer = timer;
	};
};
class HUD {
public:
	
	HUD() {};
	void AddMessage(string messageData) {
 		messageList.push_back(new Message(messageData, 60));
	};

	void Update() {
		for (int i = 0; i < messageList.size(); i++) {
			messageList.at(i)->lifeTimer--;
			if (messageList.at(i)->lifeTimer <= 0) {
				//messageList.erase(messageList.begin() + i);
			}
		}
	};
	void Draw(Renderer* ren) {
		cout << "HDU DRAW" << endl;
		cout << "MessageList Size: " << messageList.size() << endl;
		for (int i = 0; i < messageList.size(); i++) {
			cout << messageList.at(i)->data;
		}
		//cout << endl;
	}
private:
	vector<Message*> messageList;
};