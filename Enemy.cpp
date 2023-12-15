#include "Enemy.h"
#include "includes.h"

Enemy::Enemy(){}

Enemy::~Enemy(){}

void Enemy::init(std::string textureName, sf::Vector2f position, float _speed) {

	m_speed = _speed;
	m_position = position;

	// Load a Texture
	m_texture.loadFromFile("/home/rafael/graphs/SFML/Zeca_Urubu_novo .jpg");

	// Create Sprite and Attach a Texture
	m_sprite.setTexture(m_texture);    //todas as propriedades e funcionalidades do vilão 
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2); //onde ele vai espawnar 

}

void Enemy::update(float dt) {

	m_sprite.move(m_speed * dt, 0); //update

}


sf::Sprite Enemy::getSprite() {  //Sprite é para executar a textura ou imagem

	return m_sprite;
}