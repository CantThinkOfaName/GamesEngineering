
//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#define _USE_MATH_DEFINES
#define M_PI           3.14159265358979323846  /* pi */
#include <iostream> 
#include <fstream> 
#include <math.h>
#include "json\json.h"
#include "Ship.h"
using namespace std;

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

void wrapAround(sf::Sprite * ship, sf::Vector2f boundary, sf::Vector2f size){
	 

	if (ship->getPosition().x > boundary.x){
		ship->setPosition(-size.x, ship->getPosition().y);
		cout << "wrapAround 1";
	}
	if (ship->getPosition().x < -size.x){
		ship->setPosition(boundary.x, ship->getPosition().y);
		cout << "wrapAround 2";
	}
	if (ship->getPosition().y > boundary.y){
		ship->setPosition(ship->getPosition().x, -size.y);
		cout << "wrapAround 3";
	}
	if (ship->getPosition().y < -size.y){
		ship->setPosition(ship->getPosition().x, boundary.y);
		cout << "wrapAround 4";
	}

};

int main()
{

	// Create the main window 
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "AI Lab 1");

	// Create a clock for measuring time elapsed     
	sf::Clock Clock;
	sf::Sprite shipOne;
	sf::Vector2f shipOneSize;
	sf::Sprite shipTwo;
	sf::Vector2f shipTwoSize;
	sf::Texture textureOne;
	sf::Texture textureTwo;
	sf::Vector2f shipOneVel;
	sf::Vector2f shipTwoVel;
	sf::Vector2f shipOneMove;
	if (!textureOne.loadFromFile("shipOne.png"))
	{
		
	}
	if (!textureTwo.loadFromFile("shipTwo.png"))
	{

	}
	shipOne.setTexture(textureOne);
	shipOneSize = sf::Vector2f(textureOne.getSize().x, textureOne.getSize().y);
	shipTwo.setTexture(textureTwo);
	shipTwoSize = sf::Vector2f(textureTwo.getSize().x, textureTwo.getSize().y);
	shipOne.setPosition(200, 200);
	shipOne.setOrigin(textureOne.getSize().x / 2, textureOne.getSize().y / 2);
	shipTwo.setPosition(450, 450);
	shipOneVel = sf::Vector2f(1, 0);
	shipTwoVel = sf::Vector2f(-2, -2);
	App.setFramerateLimit(60);
	ShipBridge hShip;
	hShip->loadTexture(textureTwo);
	hShip->SetPosition(sf::Vector2f(300, 600));
	LazyShip::GetInstance()->loadTexture(textureTwo);
	LazyShip::GetInstance()->SetPosition(sf::Vector2f(600, 200));
	// Start game loop 
	while (App.isOpen())
	{
		// Process events 
		sf::Event Event;
		float angle = shipOne.getRotation() * M_PI / 180;
		//float angle = shipOne.getRotation();
		while (App.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				App.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				App.close();

			if (Event.type == sf::Event::KeyPressed){
				if (Event.key.code == sf::Keyboard::Right){
					shipOne.rotate(1);
				}
				else if (Event.key.code == sf::Keyboard::Left){
					shipOne.rotate(-1);
				}
				if (Event.key.code == sf::Keyboard::Up){
					shipOne.move(cos(angle) * 3, sin(angle) * -3);
				}
				else if (Event.key.code == sf::Keyboard::Down){
					shipOne.move(cos(angle) * -3, sin(angle) * 3);
				}
			}
		}  
		cout << "Ship Angle: " << shipOne.getRotation() << "\n";
		
		//shipOneMove = sf::Vector2f(-sin(angle) * shipOneVel.x, -cos(angle)*shipOneVel.x);
		//shipOne.setPosition(shipOne.getPosition().x + shipOneMove.x, shipOne.getPosition().y + shipOneMove.y);

		shipTwo.setPosition(shipTwo.getPosition().x + shipOneVel.x, shipTwo.getPosition().y + shipOneVel.y);
		float x = shipOne.getPosition().x;
		//cout << "Ship Position: " << x;
		wrapAround(&shipOne, (sf::Vector2f)App.getSize(), shipOneSize);
		wrapAround(&shipTwo, (sf::Vector2f)App.getSize(), shipTwoSize);
		hShip->update();
		LazyShip::GetInstance()->update();
		App.clear();
		App.draw(shipOne); 
		App.draw(shipTwo);
		App.draw(*hShip->getSprite());
		App.draw(*LazyShip::GetInstance()->getSprite());
		// Finally, display rendered frame on screen 
		App.display();
	}

	return EXIT_SUCCESS;
}