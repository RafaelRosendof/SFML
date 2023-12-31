#include "includes.h"
#include "Hero.h"

Hero::Hero(){}  //constructor 


Hero::~Hero(){} //destructor

void Hero::init(std::string textureName, sf::Vector2f position, float mass){
	//iniciando o heroi, função init
	m_position = position;
	m_mass = mass;

	m_grounded = false;
	
	// Load a Texture
	m_texture.loadFromFile("/home/rafael/graphs/SFML/lula_molusco.jpeg");

	// Create Sprite and Attach a Texture
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);

}

void Hero::update(float dt){  //exemplo de herança 

	m_velocity -= m_mass * m_gravity * dt;  //definimos coisas como gravidade

	m_position.y -= m_velocity * dt; // velocidade no y 

	m_sprite.setPosition(m_position);


	if (m_position.y >= 800 * 0.75) {

		m_position.y = 800 * 0.75;
		m_velocity = 0;
		m_grounded = true;
		jumpCount = 0;
	}

}

void Hero::jump(float velocity){  

	if (jumpCount < 2) {
		jumpCount++;

		m_velocity = velocity;
		m_grounded = false;
	}

}

sf::Sprite Hero::getSprite(){

	return m_sprite;
}