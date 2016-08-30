#include <iostream>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
using namespace std;

class Ship {
private:
	sf::Sprite m_sprite;
	sf::Vector2f m_velocity = sf::Vector2f(-5, -5);
	sf::Texture m_texture;
public:
	Ship(){

	}
	void loadTexture(sf::Texture texture){
		m_texture = texture;
		m_sprite.setTexture(m_texture);
	}
	void SetPosition(sf::Vector2f pos){
		m_sprite.setPosition(pos);
	}
	void update(){
		cout << "Updating Ship" << endl;
		m_sprite.setPosition(m_sprite.getPosition().x + m_velocity.x, m_sprite.getPosition().y + m_velocity.y);
	}
	sf::Sprite * getSprite(){
		return &m_sprite;
	}
};

class ShipBridge{
public:
	ShipBridge() : ship(new Ship()){

	}
	Ship* operator->() { return ship; }
private:
	Ship* ship;
};

class LazyShip {
public:

	static LazyShip* GetInstance();
	void loadTexture(sf::Texture texture);
	void SetPosition(sf::Vector2f pos);
	void update();
	sf::Sprite * getSprite();
private:
	sf::Sprite m_sprite;
	sf::Vector2f m_velocity = sf::Vector2f(-5, -5);
	sf::Texture m_texture;
	LazyShip(){}

};
