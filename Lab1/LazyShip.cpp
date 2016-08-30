#include "stdafx.h"
#include "Ship.h"
static LazyShip* instance;

LazyShip* LazyShip::GetInstance(){
	if (instance){
		return instance;
	}
	else{
		instance = new LazyShip();
		return instance;
	}
};
void LazyShip::loadTexture(sf::Texture texture){
	m_texture = texture;
	m_sprite.setTexture(m_texture);
}
void LazyShip::SetPosition(sf::Vector2f pos){
	m_sprite.setPosition(pos);
}
void LazyShip::update(){
	cout << "Updating LazyShip" << endl;
	m_sprite.setPosition(m_sprite.getPosition().x + m_velocity.x, m_sprite.getPosition().y + m_velocity.y);
}
sf::Sprite * LazyShip::getSprite(){
	return &m_sprite;
}