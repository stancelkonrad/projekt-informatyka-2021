/*
Temat projektu: Gra dinozaur
Zakres indywidualny: Gra polega na poruszaniu siê dinozaurem i unikaniu przeszkód.
Z biegiem czasu prêdkoœæ gry (animacji i tworzenia przeszkód) przyspiesza i pojawia siê wiêcej przeszkód.
Gra oparta na grze offline w przegl¹darce Google Chrome.
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <sfml/graphics.hpp>
#include <iostream>
#include <time.h>
#include <windows.h>

#define MENU_LINES 3
#define HELP_LINES 4

#define HEIGHT_STAND 66

#define START_POSITION_X 100
#define START_POSITION_Y 395

#define PLAYER_SPRITE_WIDTH 24
#define PLAYER_SPRITE_HEIGHT 24
#define PLAYER_SPRITE_WALK_START 4
#define PLAYER_SPRITE_WALK_END 9
#define PLAYER_SPRITE_JUMP 12


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
	help[3].setString("ESC - EXIT");
	help[3].setCharacterSize(20);
	help[3].setPosition(sf::Vector2f((width / 2) - help[3].getLocalBounds().width / 2, 150 + (height / (2))));
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
	};
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
	punktyTekst.setPosition(40, 40);
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
		ySpeed += 5000*dt;
	}
}

void Player::anim() {

	if (jumping) {
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

void Player::draw(sf::RenderWindow& window) {
	sprite.setPosition(self.getPosition());
	window.draw(sprite);
	window.draw(punktyTekst);
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

	strcpy(playerschar[0].nazwa, "EMPTY");
	strcpy(playerschar[1].nazwa, "EMPTY");
	strcpy(playerschar[2].nazwa, "EMPTY");
	strcpy(playerschar[3].nazwa, "EMPTY");
	strcpy(playerschar[4].nazwa, "EMPTY");

	for (int i = 0; i < 5; i++)
	{
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
		Np = 5;
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
	for (int i = 0; i < Np; i++)
	{
		window.draw(title);
		window.draw(players[i]);
	}
}

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

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Dino SFML");
	Menu menu(window.getSize().x, window.getSize().y);
	Pause pause(window.getSize().x, window.getSize().y);
	Help help(window.getSize().x, window.getSize().y);
	
	sf::Texture background;
	background.loadFromFile("assets/background.png");
	sf::Sprite backgroundSprite(background, sf::IntRect(0,0,800,600));

	Player player;
	int menu_selected_flag = 0;
	sf::Clock zegar;
	sf::Clock dtClock;
	FILE* file;
	if (file = fopen("players.dat", "r"))
		std::cout << "'players.dat' already exists";
	else
	{
		std::cout << "Creating new 'players.dat'";
		players_to_file();
	}
	playersPoints pl1;
	//strcpy(pl1.nazwa, "Guy");
	//pl1.liczb_pkt = 18000;
	players_list* highscores = new players_list(5);
	//pl->zapisz(pl1);
	highscores->sort();
	highscores->load();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					myDelay(100);
					if (menu_selected_flag == 0)
						menu.przesunG();
					else if (menu_selected_flag == 3)
						pause.przesunG();
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					myDelay(100);
					if (menu_selected_flag == 0)
						menu.przesunD();
					else if (menu_selected_flag == 3)
						pause.przesunD();
				}
				if (menu_selected_flag == 0)
				{
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
					{
						std::cout << "Launching game\n";
						menu_selected_flag = 1;
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
			player.update(window, dt);
			player.draw(window);
		}
		else if (menu_selected_flag == 2)
			exit(0);
		else if (menu_selected_flag == 3)
			pause.draw(window);
		else if (menu_selected_flag == 4)
			help.draw(window);
		else if (menu_selected_flag == 5)
			highscores->draw(window);
		window.display();
	}
	return 0;
}