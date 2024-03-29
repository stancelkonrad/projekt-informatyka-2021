﻿/*
Temat projektu: Gra dinozaur
Zakres indywidualny: Gra polega na poruszaniu się dinozaurem i unikaniu przeszkód.
Z biegiem czasu prędkość gry (animacji i tworzenia przeszkód) przyspiesza i pojawia się więcej przeszkód.
Gra oparta na grze offline w przeglądarce Google Chrome.
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <sfml/graphics.hpp>
#include <iostream>
#include <time.h>
#include <windows.h>
#include <string>

#define MENU_LINES 3
#define HELP_LINES 5

#define HEIGHT_STAND 66

#define START_POSITION_X 100
#define START_POSITION_Y 395

#define OBSTACLE_SPAWN_X 810
#define OBSTACLE_SPAWN_Y 395

#define PLAYER_SPRITE_WIDTH 24
#define PLAYER_SPRITE_HEIGHT 24
#define PLAYER_SPRITE_WALK_START 4
#define PLAYER_SPRITE_WALK_END 9
#define PLAYER_SPRITE_JUMP 12
#define PLAYER_SPRITE_DEAD 14



void myDelay(int opoznienie)
{
	sf::Clock zegar;
	sf::Time czas;
	while (1)
	{
		czas = zegar.getElapsedTime();
		if (czas.asMilliseconds() > opoznienie)
		{
			zegar.restart();
			break;
		}
	}
}

class Menu
{
private:
	sf::Font font;
	sf::Text menu[MENU_LINES];
	sf::Text title;
	int selectedItem = 0;

public:
	Menu(float width, float height);
	~Menu() {};
	void przesunG();
	void przesunD();
	int getSelectedItem() { return selectedItem; }
	void draw(sf::RenderWindow& window);
};

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("assets/SuperLegendBoy.ttf"))
	{
		return;
	}
	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setString("DINO GAME");
	title.setStyle(sf::Text::Bold);
	title.setPosition(sf::Vector2f((width / 2) - title.getLocalBounds().width / 2, 40));

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Black);
	menu[0].setString("START");
	menu[0].setPosition(sf::Vector2f((width / 2) - menu[0].getLocalBounds().width / 2, height / MENU_LINES));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color(120, 120, 120));
	menu[1].setString("HIGHSCORES");
	menu[1].setPosition(sf::Vector2f((width / 2) - menu[1].getLocalBounds().width / 2, 50 + (height / MENU_LINES)));
	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color(120, 120, 120));
	menu[2].setString("EXIT");
	menu[2].setPosition(sf::Vector2f((width / 2) - menu[2].getLocalBounds().width / 2, 100 + (height / MENU_LINES)));
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MENU_LINES; i++)
	{
		window.draw(title);
		window.draw(menu[i]);
	}
}

void Menu::przesunG()
{
	if (selectedItem >= 0 && selectedItem < MENU_LINES)
	{
		menu[selectedItem].setFillColor(sf::Color(120, 120, 120));
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = MENU_LINES - 1;
		menu[selectedItem].setFillColor(sf::Color::Black);
	}
}

void Menu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < MENU_LINES)
	{
		menu[selectedItem].setFillColor(sf::Color(120, 120, 120));
		selectedItem++;
		if (selectedItem >= MENU_LINES)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Black);
	}
}

class Pause
{
private:
	sf::Font font;
	sf::Text pause[2];
	sf::Text title;
	int selectedItem = 0;

public:
	Pause(float width, float height);
	~Pause() {};
	void przesunG();
	void przesunD();
	int getSelectedItem() { return selectedItem; };
	void resetSelectedItem() { selectedItem = 0; };
	void draw(sf::RenderWindow& window);
};

Pause::Pause(float width, float height)
{
	if (!font.loadFromFile("assets/SuperLegendBoy.ttf"))
	{
		return;
	}
	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setString("PAUSE");
	title.setStyle(sf::Text::Bold);
	title.setPosition(sf::Vector2f((width / 2) - title.getLocalBounds().width / 2, 40));

	pause[0].setFont(font);
	pause[0].setFillColor(sf::Color::Black);
	pause[0].setString("CONTINUE");
	pause[0].setPosition(sf::Vector2f((width / 2) - pause[0].getLocalBounds().width/2, height / (2) * 1));
	pause[1].setFont(font);
	pause[1].setFillColor(sf::Color(120, 120, 120));
	pause[1].setString("MAIN MENU");
	pause[1].setPosition(sf::Vector2f((width / 2) - pause[1].getLocalBounds().width / 2, 50 + (height / (2) * 1)));
}

void Pause::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 2; i++)
	{
		window.draw(title);
		window.draw(pause[i]);
	}
}

void Pause::przesunG()
{
	if (selectedItem >= 0 && selectedItem < 2)
	{
		pause[selectedItem].setFillColor(sf::Color(120, 120, 120));
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = 1;
		pause[selectedItem].setFillColor(sf::Color::Black);
	}
}

void Pause::przesunD()
{
	if (selectedItem >= 0 && selectedItem < 2)
	{
		pause[selectedItem].setFillColor(sf::Color(120, 120, 120));
		selectedItem++;
		if (selectedItem >= 2)
			selectedItem = 0;
		pause[selectedItem].setFillColor(sf::Color::Black);
	}
}

class DifficultyMenu
{
private:
	sf::Font font;
	sf::Text difficultyMenu[2];
	sf::Text title;
	int selectedItem = 0;

public:
	DifficultyMenu(float width, float height);
	~DifficultyMenu() {};
	void przesunG();
	void przesunD();
	int getSelectedItem() { return selectedItem; };
	void resetSelectedItem() { selectedItem = 0; };
	void draw(sf::RenderWindow& window);
};

DifficultyMenu::DifficultyMenu(float width, float height)
{
	if (!font.loadFromFile("assets/SuperLegendBoy.ttf"))
	{
		return;
	}
	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setString("CHOOSE DIFFICULTY");
	title.setStyle(sf::Text::Bold);
	title.setPosition(sf::Vector2f((width / 2) - title.getLocalBounds().width / 2, 40));

	difficultyMenu[0].setFont(font);
	difficultyMenu[0].setFillColor(sf::Color::Black);
	difficultyMenu[0].setString("EASY");
	difficultyMenu[0].setPosition(sf::Vector2f((width / 2) - difficultyMenu[0].getLocalBounds().width / 2, height / (2) * 1));
	difficultyMenu[1].setFont(font);
	difficultyMenu[1].setFillColor(sf::Color(120, 120, 120));
	difficultyMenu[1].setString("HARD");
	difficultyMenu[1].setPosition(sf::Vector2f((width / 2) - difficultyMenu[1].getLocalBounds().width / 2, 50 + (height / (2) * 1)));
}

void DifficultyMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 2; i++)
	{
		window.draw(title);
		window.draw(difficultyMenu[i]);
	}
}

void DifficultyMenu::przesunG()
{
	if (selectedItem >= 0 && selectedItem < 2)
	{
		difficultyMenu[selectedItem].setFillColor(sf::Color(120, 120, 120));
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = 1;
		difficultyMenu[selectedItem].setFillColor(sf::Color::Black);
	}
}

void DifficultyMenu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < 2)
	{
		difficultyMenu[selectedItem].setFillColor(sf::Color(120, 120, 120));
		selectedItem++;
		if (selectedItem >= 2)
			selectedItem = 0;
		difficultyMenu[selectedItem].setFillColor(sf::Color::Black);
	}
}

class PlayerNameMenu
{
private:
	sf::Font font;
	sf::Text playerName;
	sf::Text title[3];
	std::string Name = "";
	int selectedItem = 0;

public:
	PlayerNameMenu(float width, float height);
	~PlayerNameMenu() {};
	std::string getName() { return Name; };
	void addLetter(char letter);
	void removeLetter();
	void draw(sf::RenderWindow& window);
	void refresh(float width, float height);
};

void PlayerNameMenu::addLetter(char letter)
{ 
	Name += std::string(1, letter); 
	playerName.setString(Name + "_");
}

void PlayerNameMenu::removeLetter()
{
	if (!Name.empty())
		Name.pop_back(); 
	playerName.setString(Name + "_");
}

PlayerNameMenu::PlayerNameMenu(float width, float height)
{
	if (!font.loadFromFile("assets/SuperLegendBoy.ttf"))
	{
		return;
	}
	title[0].setFont(font);
	title[0].setFillColor(sf::Color::Black);
	title[0].setString("GAME OVER");
	title[0].setStyle(sf::Text::Bold);
	title[0].setPosition(sf::Vector2f((width / 2) - title[0].getLocalBounds().width / 2, 40));
	title[1].setFont(font);
	title[1].setFillColor(sf::Color::Black);
	title[1].setString("ENTER PLAYER NAME");
	title[1].setStyle(sf::Text::Regular);
	title[1].setPosition(sf::Vector2f((width / 2) - title[1].getLocalBounds().width / 2, 80));

	playerName.setFont(font);
	playerName.setFillColor(sf::Color::Black);
	playerName.setString(Name + "_");
	playerName.setPosition(sf::Vector2f((width / 2) - playerName.getLocalBounds().width / 2, height / (2) * 1));
}

void PlayerNameMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 2; i++)
	{
		window.draw(title[i]);
		window.draw(playerName);
	}
}

void PlayerNameMenu::refresh(float width, float height)
{
	playerName.setString(Name + "_");
	playerName.setPosition(sf::Vector2f((width / 2) - playerName.getLocalBounds().width / 2, height / (2) * 1));
}

class Help
{
private:
	sf::Font font;
	sf::Text help[HELP_LINES];
	sf::Text title;

public:
	Help(float width, float height);
	~Help() {};
	void draw(sf::RenderWindow& window);
};

Help::Help(float width, float height)
{
	if (!font.loadFromFile("assets/SuperLegendBoy.ttf"))
	{
		return;
	}
	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setString("HELP");
	title.setStyle(sf::Text::Bold);
	title.setPosition(sf::Vector2f((width / 2) - title.getLocalBounds().width / 2, 40));

	help[0].setFont(font);
	help[0].setFillColor(sf::Color::Black);
	help[0].setString("RULES: JUST AVOID OBSTACLES BY JUMPING");
	help[0].setCharacterSize(20);
	help[0].setPosition(sf::Vector2f((width / 2) - help[0].getLocalBounds().width / 2, height / (3)));
	help[1].setFont(font);
	help[1].setFillColor(sf::Color::Black);
	help[1].setString("JUMP - SPACE");
	help[1].setCharacterSize(20);
	help[1].setPosition(sf::Vector2f((width / 2) - help[1].getLocalBounds().width / 2, 50 + height / (2)));
	help[2].setFont(font);
	help[2].setFillColor(sf::Color::Black);
	help[2].setString("PAUSE - PAUSE");
	help[2].setCharacterSize(20);
	help[2].setPosition(sf::Vector2f((width / 2) - help[2].getLocalBounds().width / 2, 100 + (height / (2))));
	help[3].setFont(font);
	help[3].setFillColor(sf::Color::Black);
	help[3].setString("INSTANT DEATH - F2");
	help[3].setCharacterSize(20);
	help[3].setPosition(sf::Vector2f((width / 2) - help[3].getLocalBounds().width / 2, 150 + (height / (2))));
	help[4].setFont(font);
	help[4].setFillColor(sf::Color::Black);
	help[4].setString("ESC - EXIT");
	help[4].setCharacterSize(20);
	help[4].setPosition(sf::Vector2f((width / 2) - help[4].getLocalBounds().width / 2, 200 + (height / (2))));
}

void Help::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < HELP_LINES; i++)
	{
		window.draw(title);
		window.draw(help[i]);
	}
}

class Player {
private:
	sf::RectangleShape self;
	sf::Image spritesheet;
	sf::Sprite sprite;
	sf::Texture tekstura;
	sf::Font font;
	sf::Text punktyTekst;

	sf::Clock clock;
	sf::Clock zegarPunkty;
	sf::Clock zegarAnimacja;

	bool jumping = false;
	float ySpeed;
	int punkty = 0;
	bool isDead = false;

	void walk();
	void jump(float dt);
	void anim();

public:
	Player();
	sf::FloatRect getGlobalBounds();
	void update(sf::RenderTarget& render, float dt);
	void draw(sf::RenderWindow& window);
	void reset() {
		punkty = 0;
		clock.restart();
		zegarPunkty.restart();
		zegarAnimacja.restart();
		isDead = false;
	}
	int getPoints() { return punkty; };
	void dead() {
		isDead = true;
		anim();
	};
	bool isPlayerDead() { return isDead; };
};

Player::Player()
{
	self = sf::RectangleShape(sf::Vector2f(30, HEIGHT_STAND));
	self.setFillColor(sf::Color::Green);
	self.setPosition(START_POSITION_X, START_POSITION_Y);
	punkty = 0;

	if (!font.loadFromFile("assets/SuperLegendBoy.ttf"))
	{
		return;
	}
	punktyTekst.setFont(font);
	punktyTekst.setPosition(20, 20);
	punktyTekst.setCharacterSize(24);
	punktyTekst.setFillColor(sf::Color::Black);
	punktyTekst.setString("Score: 0");

	spritesheet.loadFromFile("assets/dino.png");
}

void Player::walk() {
	if (self.getPosition().y > START_POSITION_Y) {
		jumping = false;
		ySpeed = 0;
		self.setPosition(self.getPosition().x, START_POSITION_Y);
	}
}

void Player::jump(float dt) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !jumping) {
		jumping = true;
		ySpeed = -1000;
	}
	if (jumping) {
		ySpeed += 3300*dt;
	}
}

void Player::draw(sf::RenderWindow& window) {
	sprite.setPosition(self.getPosition());
	window.draw(sprite);
	window.draw(punktyTekst);
}

void Player::anim() {
	if (isDead) {
		tekstura.loadFromImage(spritesheet, sf::IntRect(PLAYER_SPRITE_DEAD * PLAYER_SPRITE_WIDTH, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT));
		myDelay(1000);
		return;
	}
	else if (jumping) {
		tekstura.loadFromImage(spritesheet, sf::IntRect(PLAYER_SPRITE_JUMP * PLAYER_SPRITE_WIDTH, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT));
	}
	else
	{
		int predkoscAnimacja = 100 - (int)clock.getElapsedTime().asSeconds();
		float klatkaSzybkosc;
		if (predkoscAnimacja < 30)
			klatkaSzybkosc = 30;
		else
			klatkaSzybkosc = predkoscAnimacja;
		int klatka = zegarAnimacja.getElapsedTime().asMilliseconds() / klatkaSzybkosc;
		int spriteKlatka = PLAYER_SPRITE_WALK_START + klatka;

		if (spriteKlatka > PLAYER_SPRITE_WALK_END) {
			zegarAnimacja.restart();
			spriteKlatka = PLAYER_SPRITE_WALK_START;
		}
		tekstura.loadFromImage(spritesheet, sf::IntRect(spriteKlatka * PLAYER_SPRITE_WIDTH, 0, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT));
		sprite.setTexture(tekstura);
		sprite.setScale(sf::Vector2f(4, 4));
		sprite.setOrigin(12.5f, 21);
	}
}

sf::FloatRect Player::getGlobalBounds() {
	return self.getGlobalBounds();
}

void Player::update(sf::RenderTarget& render, float dt) {
	if (isDead)
	{
		anim();
		return;
	}
	if (zegarPunkty.getElapsedTime().asMilliseconds() > 400) {
		zegarPunkty.restart();
		punkty += 1;
	}

	punktyTekst.setString("Points: " + std::to_string(punkty));
	jump(dt);
	anim();
	self.move(0, ySpeed * dt);
	walk();
}


typedef struct {
	char nazwa[20];
	int liczb_pkt;
} playersPoints;

void players_to_file()
{
	srand(time(NULL));
	playersPoints playerschar[10];

	FILE* file;
	file = fopen("players.dat", "w+b");

	for (int i = 0; i < 5; i++)
	{
		strcpy(playerschar[i].nazwa, "EMPTY");
		playerschar[i].liczb_pkt = 0;
	}

	fwrite(playerschar, sizeof(playersPoints), 5, file);
	fclose(file);
}

int compare(const void* left, const void* right) {
	const playersPoints* a = (const playersPoints*)left;
	const playersPoints* b = (const playersPoints*)right;
	if (a->liczb_pkt > b->liczb_pkt) {
		return -1;
	}
	else if (a->liczb_pkt < b->liczb_pkt) {
		return 1;
	}
	else {
		return 0;
	}
}

class players_list {
private:
	sf::Text* players;
	sf::Text title;
	playersPoints* player_char;
	sf::Font font;
	int Np;
public:
	players_list(int N);
	void load();
	void sort();
	void save(playersPoints pl);
	void read();
	void draw(sf::RenderWindow& window);
};

void players_list::save(playersPoints pl)
{
	FILE* file;
	file = fopen("players.dat", "a+b");
	fwrite(&pl, sizeof(playersPoints), 1, file);
	fclose(file);
	this->read();
}

void players_list::read()
{
	FILE* file = fopen("players.dat", "r+b");
	unsigned int rozmiar_plik = 0, ile_graczy = 0;
	fseek(file, 0, SEEK_END);
	rozmiar_plik = ftell(file);
	ile_graczy = rozmiar_plik / sizeof(playersPoints);
	rewind(file);
	if (ile_graczy > 0)
		if (ile_graczy != Np)
		{
			Np = ile_graczy;
			delete[] player_char;
			delete[] players;
			players = new sf::Text[Np];
			player_char = new playersPoints[Np];
			fread(player_char, sizeof(playersPoints), Np, file);
		}
	fclose(file);
}

players_list::players_list(int N)
{

	if (!font.loadFromFile("assets/SuperLegendBoy.ttf"))
	{
		return;
	}

	FILE* file = fopen("players.dat", "r+b");
	unsigned int rozmiar_plik = 0, ile_graczy = 0;
	fseek(file, 0, SEEK_END);
	rozmiar_plik = ftell(file);
	ile_graczy = rozmiar_plik / sizeof(playersPoints);
	if (N > ile_graczy)
	{
		Np = 20;
	}
	else
	{
		Np = N;
	}

	players = new sf::Text[Np];
	player_char = new playersPoints[Np];

	rewind(file);
	fread(player_char, sizeof(playersPoints), Np, file);
	fclose(file);

	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setString("HIGHSCORES");
	title.setStyle(sf::Text::Bold);
	title.setPosition(sf::Vector2f((800 / 2) - title.getLocalBounds().width / 2, 40));

	for (int i = 0; i < Np; i++)
	{
		players[i].setFont(font);
		players[i].setFillColor(sf::Color::Black);
		players[i].setPosition(10 + 800 / 4, 600 / 3 + i * 50);

	}
}

void players_list::load()
{
	std::string tmp_tekst;

	title.setFont(font);
	title.setFillColor(sf::Color::Black);
	title.setString("HIGHSCORES");
	title.setStyle(sf::Text::Bold);
	title.setPosition(sf::Vector2f((800 / 2) - title.getLocalBounds().width / 2, 40));

	for (int i = 0; i < Np; i++)
	{
		players[i].setFont(font);
		players[i].setFillColor(sf::Color::Black);
		players[i].setPosition(10 + 800 / 4, 600 / 3 + i * 50);

		tmp_tekst.assign(player_char[i].nazwa);
		tmp_tekst += "    " + std::to_string(player_char[i].liczb_pkt);
		players[i].setString(tmp_tekst);
	}
}

void players_list::sort()
{
	qsort(player_char, Np, sizeof(playersPoints), compare);
}

void players_list::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 5; i++)
	{
		window.draw(title);
		window.draw(players[i]);
	}
}

class Obstacle {
private:
	sf::RectangleShape self;
	sf::Image spritesheet;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Clock animClock;
	float speed;
public:
	explicit Obstacle(float speed);
	void setPosition(sf::Vector2f vec2f);
	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	void update(float dt);
	void draw(sf::RenderWindow& render);
};

Obstacle::Obstacle(float speed) {

	spritesheet.loadFromFile("assets/cactus.png");
	this->speed = speed;
	self = sf::RectangleShape(sf::Vector2f(10, 14));
	self.setFillColor(sf::Color::Red);

}

void Obstacle::setPosition(sf::Vector2f vec2f) {
	self.setPosition(vec2f);
}

sf::Vector2f Obstacle::getPosition() {
	return self.getPosition();
}

sf::FloatRect Obstacle::getGlobalBounds() {
	return self.getGlobalBounds();
}

void Obstacle::draw(sf::RenderWindow& window) {
	sprite.setPosition(self.getPosition());
	window.draw(sprite);
}

void Obstacle::update(float dt) {
	texture.loadFromImage(spritesheet, sf::IntRect(0, 0, 10, 14));
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(-4, 4));
	sprite.setOrigin(0, 14);
	self.move(-this->speed * dt *0.5, 0);
}

class ObstacleGenerator {
private:
	std::vector <Obstacle> self;
	Player& player;
	sf::Clock clock;
	sf::Clock spawnClock;
	void add(sf::Vector2f vec2f);
	int difficulty = 0;
public:
	explicit ObstacleGenerator(Player& ref_player);
	void spawn();
	void update(float dt);
	void draw(sf::RenderWindow& render);
	void reset();
};

ObstacleGenerator::ObstacleGenerator(Player& ref_player) : player(ref_player) {
}

void ObstacleGenerator::add(sf::Vector2f vec2f) {
	float multiplier = clock.getElapsedTime().asSeconds();
	Obstacle obstacle(500 + multiplier * 10);
	obstacle.setPosition(vec2f);
	self.push_back(obstacle);
}

void ObstacleGenerator::spawn() {
	float time = spawnClock.getElapsedTime().asSeconds();
	float multiplier = clock.getElapsedTime().asSeconds();
	if (time > 1 - (multiplier * 0.01)) {
		spawnClock.restart();
		add(sf::Vector2f(OBSTACLE_SPAWN_X, OBSTACLE_SPAWN_Y));
	}
}

void ObstacleGenerator::update(float dt) {
	spawn();

	for (auto obstacle = self.begin(); obstacle != self.end();) {
		obstacle->update(dt);
		if (obstacle->getGlobalBounds().intersects(player.getGlobalBounds())) {
			std::cout << "DEAD";
			player.dead();
		}
		if (obstacle->getPosition().x < -50) {
			obstacle = self.erase(obstacle);
		}
		else {
			++obstacle;
		}
	}
}

void ObstacleGenerator::draw(sf::RenderWindow& render) {
	for (auto& obstacle : self) {
		obstacle.draw(render);
	}
}

void ObstacleGenerator::reset() {
	clock.restart();
	spawnClock.restart();
	self = std::vector<Obstacle>();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Dino SFML");
	Menu menu(window.getSize().x, window.getSize().y);
	Pause pause(window.getSize().x, window.getSize().y);
	Help help(window.getSize().x, window.getSize().y);
	DifficultyMenu difficultyMenu(window.getSize().x, window.getSize().y);
	PlayerNameMenu gameover(window.getSize().x, window.getSize().y);

	Player player;
	ObstacleGenerator obstacleGenerator(player);



	sf::Texture background;
	background.loadFromFile("assets/background.png");
	sf::Sprite backgroundSprite(background, sf::IntRect(0,0,800,600));

	int menu_selected_flag = 0;
	sf::Clock zegar;
	sf::Clock dtClock;
	FILE* file;
	if (file = fopen("players.dat", "r"))
		std::cout << "'players.dat' already exists\n";
	else
	{
		std::cout << "Creating new 'players.dat'\n";
		players_to_file();
	}
	playersPoints pl1;
	players_list* highscores = new players_list(5);
	highscores->sort();
	highscores->load();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (menu_selected_flag == 7 && event.type == sf::Event::TextEntered && event.key.code != 8)
			{
					if (event.text.unicode < 0x80)
					{
						gameover.addLetter((char)event.text.unicode);
						gameover.draw(window);
					}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (menu_selected_flag == 7 && event.key.code == sf::Keyboard::Enter)
				{
					strcpy(pl1.nazwa, gameover.getName().c_str());
					pl1.liczb_pkt = player.getPoints();
					highscores->save(pl1);
					std::cout << "Displaying Highscores\n";
					obstacleGenerator.reset();
					player.reset();
					zegar.restart();
					dtClock.restart();
					menu_selected_flag = 5;
					highscores->sort();
				}
				if (menu_selected_flag == 7 && event.key.code == sf::Keyboard::BackSpace)
				{
					gameover.removeLetter();
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					myDelay(100);
					if (menu_selected_flag == 0)
						menu.przesunG();
					else if (menu_selected_flag == 3)
						pause.przesunG();
					else if (menu_selected_flag == 6)
						difficultyMenu.przesunG();
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					myDelay(100);
					if (menu_selected_flag == 0)
						menu.przesunD();
					else if (menu_selected_flag == 3)
						pause.przesunD();
					else if (menu_selected_flag == 6)
						difficultyMenu.przesunG();
				}
				if (menu_selected_flag == 6)
				{
					if (event.key.code == sf::Keyboard::Enter && difficultyMenu.getSelectedItem() == 0)
					{
						menu_selected_flag = 1;
						std::cout << "Easy mode\n";
					}
					if (event.key.code == sf::Keyboard::Enter && difficultyMenu.getSelectedItem() == 1)
					{
						menu_selected_flag = 1;
						std::cout << "Hard mode\n";
					}
				}
				if (menu_selected_flag == 0)
				{
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
					{
						std::cout << "Launching game\n";
						menu_selected_flag = 6;
						myDelay(100);
					}
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
					{
						std::cout << "Displaying Highscores\n";
						menu_selected_flag = 5;
					}
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 2)
					{
						std::cout << "Exiting\n";
						menu_selected_flag = 2;
					}
				}
				if (menu_selected_flag == 3)
				{
					if (event.key.code == sf::Keyboard::Enter && pause.getSelectedItem() == 0)
					{
						std::cout << "Continue\n";
						menu_selected_flag = 1;
					}
					if (event.key.code == sf::Keyboard::Enter && pause.getSelectedItem() == 1)
					{
						std::cout << "Going to main menu\n";
						obstacleGenerator.reset();
						player.reset();
						zegar.restart();
						dtClock.restart();
						menu_selected_flag = 0;
					}
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					if (menu_selected_flag == 1)
					{
						std::cout << "Paused\n";
						menu_selected_flag = 3;
					}
					if (menu_selected_flag == 4)
					{
						std::cout << "Continue\n";
						menu_selected_flag = 1;
					}
					if (menu_selected_flag == 5)
					{
						std::cout << "Going to main menu\n";
						menu_selected_flag = 0;
					}
					if (menu_selected_flag == 6)
					{
						std::cout << "Going to main menu\n";
						menu_selected_flag = 0;
					}
				}
				if (event.key.code == sf::Keyboard::Pause)
				{
					if (menu_selected_flag == 1)
					{
						std::cout << "Paused\n";
						menu_selected_flag = 3;
					}
				}
				if (event.key.code == sf::Keyboard::F1)
				{
					if (menu_selected_flag == 1)
					{
						std::cout << "Help window\n";
						menu_selected_flag = 4;
					}
				}
				if (event.key.code == sf::Keyboard::F2)
				{
					std::cout << "DEAD\n";
					player.dead();
				}
			}
		}
		window.clear(sf::Color::White);
		if (menu_selected_flag == 0)
			menu.draw(window);
		else if (menu_selected_flag == 1)
		{
			sf::Time czas = dtClock.restart();
			float dt = czas.asSeconds();
			window.draw(backgroundSprite);
			obstacleGenerator.update(dt);
			player.update(window, dt);
			obstacleGenerator.draw(window);
			player.draw(window);
			if (player.isPlayerDead())
			{
				myDelay(1000);
				menu_selected_flag = 7;
			}
		}
		else if (menu_selected_flag == 2)
			exit(0);
		else if (menu_selected_flag == 3)
			pause.draw(window);
		else if (menu_selected_flag == 4)
			help.draw(window);
		else if (menu_selected_flag == 5)
		{
			//highscores->sort();
			highscores->load();
			highscores->draw(window);
		}
		else if (menu_selected_flag == 6)
			difficultyMenu.draw(window);
		else if (menu_selected_flag == 7)
		{
			gameover.refresh(window.getSize().x, window.getSize().y);
			gameover.draw(window);
		}
		window.display();
	}
	return 0;
}