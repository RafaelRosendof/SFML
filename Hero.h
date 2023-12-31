#include "includes.h"

class Hero{

public:
	Hero();
	~Hero();

	void init(std::string textureName, sf::Vector2f position, float mass);
	void update(float dt);
	void jump(float velocity); //funções de movimento 
	sf::Sprite getSprite();


private:

	int jumpCount = 0;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;  //Propriedades do heroi 
	float m_mass;			//aqui é setado tudo 
	float m_velocity;
	const float m_gravity = 9.80f;
	bool m_grounded;

};