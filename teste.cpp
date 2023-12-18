#include "includes.h"
#include "Hero.h"       //includes dos caracteres
#include "Enemy.h"
#include "Rocket.h"


sf::Vector2f viewSize(1600, 800);   //tamanho da janela
sf::VideoMode vm(viewSize.x, viewSize.y);  //estilo de reprodução
sf::RenderWindow window(vm, "Hello SFML Game !!!", sf::Style::Default);  //titulo da página

void spawnEnemy();  //ativando a função presente no enemy.cpp
void shoot();  //ativando a função de atirar

bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2);
//chacando colisão

sf::Vector2f playerPosition;   //ativando a posição do boneco
bool playerMoving = false;  //movimento do boneco 

sf::Texture skyTexture; // textura do ceu 
sf::Sprite skySprite; //ativação da textura

sf::Texture bgTexture;  //mesma coisa de cima, sendo que para o cenário
sf::Sprite bgSprite;

Hero hero;   //iniciando o heroi

std::vector<Enemy*> enemies;  //vetor de inimigos
std::vector<Rocket*> rockets;  //vetor de projéteis

float currentTime;   //tempo do jogo
float prevTime = 0.0f;



void init() {


	skyTexture.loadFromFile("Assets/graphics/sky.png");
	skySprite.setTexture(skyTexture);

	bgTexture.loadFromFile("/home/rafael/graphs/SFML/fundo.jpg");  //função para inicializar o jogo
	bgSprite.setTexture(bgTexture);
    //textura e fundo
	hero.init("Assets/graphics/hero.png", sf::Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200);
    //inicializador do heroi 
	srand((int)time(0));

}


void updateInput() {
     //aqui é a parte que é lido o teclado do jogo 
	sf::Event event;

	// while{ enquanto tiver eventos... }
	while (window.pollEvent(event)) {

		if (event.type == sf::Event::KeyPressed) {

			if (event.key.code == sf::Keyboard::Up) {


				hero.jump(750.0f);
			}

			if (event.key.code == sf::Keyboard::Down) {

				shoot();
			}

		}

		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
			window.close();  //presiona ESC e sai do jogo

	}

}


void update(float dt) {

	hero.update(dt);   //update do tempo

	currentTime += dt;

	// aprarição de inimigos 

	if (currentTime >= (prevTime + 1.125f)) {
         //atualizar o tempo do jogo
		spawnEnemy();

		prevTime = currentTime;

	}

	// Update Enemies

	for (int i = 0; i < enemies.size(); i++) {

		Enemy* enemy = enemies[i];

		enemy->update(dt);   //upando os inimigos 

		if (enemy->getSprite().getPosition().x < 0) {

			enemies.erase(enemies.begin() + i);
			delete(enemy);

		}
	}



	// Update rockets ou foguetes 

	for (int i = 0; i < rockets.size(); i++) {

		Rocket* rocket = rockets[i];

		rocket->update(dt);  // usando o objeto rocket para acessar o membro da classe 
                            //(*rocket).update(dt); == rocket -> update(dt);

		if (rocket->getSprite().getPosition().x > viewSize.x) {

			rockets.erase(rockets.begin() + i);
			delete(rocket);

		}

	}

	// parte que faz o check sobre o choque entra o foguete e o inimigo 

	for (int i = 0; i < rockets.size(); i++) {
		for (int j = 0; j < enemies.size(); j++) {

			Rocket* rocket = rockets[i];
			Enemy* enemy = enemies[j];

			if (checkCollision(rocket->getSprite(), enemy->getSprite())) {


				rockets.erase(rockets.begin() + i);
				enemies.erase(enemies.begin() + j);

				delete(rocket);
				delete(enemy);

				printf(" rocket intersects enemy \n");
			}

		}
	}



}

void draw() {   //funçã o para inicializar os desenhos 

	window.draw(skySprite);
	window.draw(bgSprite);

	window.draw(hero.getSprite());

	for (Enemy *enemy : enemies) {

		window.draw(enemy->getSprite());
	}

	for (Rocket *rocket : rockets) {

		window.draw(rocket->getSprite());
	}


}



int main() {

	sf::Clock clock;
	window.setFramerateLimit(60);  //parte do main que setamos o fps 

	init();

	while (window.isOpen()) {

		updateInput();  //entramos com o input aqui 

		sf::Time dt = clock.restart();  //cronometro
		update(dt.asSeconds());  //setamos as unidades de tempo 


		window.clear(sf::Color::White); //cor default 

		draw();  //ativa desenho 

		window.display(); //ativa display da janela 

	}

        for (Enemy* enemy : enemies) {
            delete enemy;
            }
        enemies.clear();

        for (Rocket* rocket : rockets) {
            delete rocket;
        }
        rockets.clear();

	return 0;
}


void spawnEnemy() {   //função para spawnar o inimigo 


	//printf("spawnEnemy \n");

	int randLoc = rand() % 3;  //em quais locais ele spawna, e aqui definimos a constancia 

	sf::Vector2f enemyPos;

	float speed;  //velocidade 

	switch (randLoc) {
	case 0: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.75f); speed = -400; break;
	case 1: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.60f); speed = -550; break;
	case 2: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.40f); speed = -650; break;
	default: printf("incorrect y value \n"); break; //colocamos onde ele nasce e sua velocidade
	}

	Enemy* enemy = new Enemy();  //alocação dinâmica
	enemy->init("Assets/graphics/enemy.png", enemyPos, speed); //iniciando, aqui meio que tem um construtor
	enemies.push_back(enemy);
}

void shoot() {

	Rocket* rocket = new Rocket();  //alocação dinâmica na memória 

	rocket->init("path da sua imagem", hero.getSprite().getPosition(), 400.0f);//velocidade to foguete
    //inicializador do rocket
	rockets.push_back(rocket);

}


bool checkCollision(sf::Sprite sprite1, sf::Sprite sprite2) {  //função para verificar colisão

	sf::FloatRect shape1 = sprite1.getGlobalBounds();
	sf::FloatRect shape2 = sprite2.getGlobalBounds();

	if (shape1.intersects(shape2)) {

		return true;

	}
	else {

		return false;   //aqui é a função que verifica a colisão

	}

}