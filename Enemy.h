#include "includes.h"

class Enemy
{
public:
	Enemy();
	~Enemy(); //constructor and  detructor 


	void init(std::string textureName, sf::Vector2f position, float _speed);
	void update(float dt);
	sf::Sprite getSprite();

private:

	sf::Texture m_texture;
	sf::Sprite m_sprite;    //propriedades do vilão 
	sf::Vector2f m_position;
	float m_speed;

};