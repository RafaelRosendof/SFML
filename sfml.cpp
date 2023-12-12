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

void reset();

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


int score = 0;
bool gameover = true;

// Text

sf::Font headingFont;
sf::Font scoreFont;

sf::Text headingText;
sf::Text scoreText;
sf::Text tutorialText;


void init() {


	skyTexture.loadFromFile("Assets/graphics/sky.png");
	skySprite.setTexture(skyTexture);

//	bgSprite.setTexture(bgTexture);
//	headingFont.loadFromFile("/home/rafael/graphs/CPP-Game-Development-By-Example/Chapter05/5.SFMLProject/SFMLProject/Assets/fonts/SnackerComic.ttf");

	scoreFont.loadFromFile("/home/rafael/graphs/CPP-Game-Development-By-Example/Chapter05/5.SFMLProject/SFMLProject/Assets/fonts/arial.ttf");

	scoreText.setFont(scoreFont);
	scoreText.setString("Score: 0");
	scoreText.setCharacterSize(45);
	scoreText.setFillColor(sf::Color::Red);

	sf::FloatRect scorebounds = scoreText.getLocalBounds();
	scoreText.setOrigin(scorebounds.width / 2, scorebounds.height / 2);
	scoreText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));



	bgTexture.loadFromFile("/home/rafael/graphs/SFML/fundo.jpg");  
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
				if(gameover){
					gameover = false;
					reset();
				}
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

			gameover = true;

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

				score++;
				std::string finalScore = "Score: " + std::to_string(score);

				scoreText.setString(finalScore);

				sf::FloatRect scorebounds = scoreText.getLocalBounds();
				scoreText.setOrigin(scorebounds.width / 2, scorebounds.height / 2);
				scoreText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));

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

	if (gameover) {
		window.draw(scoreText);
	}

}

void escreve() {
    std::ofstream outputFile("score.txt");  

    if (outputFile.is_open()) {
        // Write the score to the file
        outputFile << "Score: " << score << std::endl;
        
        // Close the file
        outputFile.close();
    } else {
        
        std::cerr << "Error: Unable to open the file for writing." << std::endl;
    }
}



int main() {

	sf::Clock clock;
	window.setFramerateLimit(60);  //parte do main que setamos o fps 

	init();

	while (window.isOpen()) {

		updateInput();  //entramos com o input aqui 

		sf::Time dt = clock.restart();  //cronometro
		if(!gameover)
			update(dt.asSeconds());  //setamos as unidades de tempo 


		window.clear(sf::Color::White); //cor default 

		draw();  //ativa desenho 

		window.display(); //ativa display da janela 
		
		escreve();
	}


	return 0;
}


void spawnEnemy() {   //função para spawnar o inimigo 


	//printf("spawnEnemy \n");

	int randLoc = rand() % 3;  //em quais locais ele spawna, e aqui definimos a constancia 

	sf::Vector2f enemyPos;

	float speed;  //velocidade 

	switch (randLoc) {
	case 0: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.75f); speed = -490; break;
	case 1: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.60f); speed = -650; break;
	case 2: enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.40f); speed = -750; break;
	default: printf("incorrect y value \n"); break; //colocamos onde ele nasce e sua velocidade
	}

	Enemy* enemy = new Enemy();
	enemy->init("Assets/graphics/enemy.png", enemyPos, speed); //iniciando, aqui meio que tem um construtor
	enemies.push_back(enemy);
}

void shoot() {

	Rocket* rocket = new Rocket();  //tiro e muito tiro 

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

		return false;

	}

}

void reset() {

	score = 0;
	currentTime = 0.0f;
	prevTime = 0.0;

	scoreText.setString("Score: 0");

	for (Enemy *enemy : enemies) {

		delete(enemy);
	}

	for (Rocket *rocket : rockets) {

		delete(rocket);
	}

	enemies.clear();
	rockets.clear();

}

