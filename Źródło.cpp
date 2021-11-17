/*
Temat projektu: Gra dinozaur
Zakres indywidualny: Gra polega na poruszaniu siê dinozaurem i unikaniu przeszkód.
Z biegiem czasu prêdkoœæ gry (animacji i tworzenia przeszkód) przyspiesza i pojawia siê wiêcej przeszkód.
Gra oparta na grze offline w przegl¹darce Google Chrome.
*/

#include <sfml/graphics.hpp>
#include <iostream>
#include <time.h>

#define MENU_LINES 2

#define HEIGHT_STAND 66

#define START_POSITION_X 100
#define START_POSITION_Y 450

#define SPRITE_WIDTH 24
#define SPRITE_HEIGHT 24
#define SPRITE_WALK_START 4
#define SPRITE_WALK_END 9

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
	title.setPosition(sf::Vector2f(width / 3, 10));

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Black);
	menu[0].setString("START");
	menu[0].setPosition(sf::Vector2f(width / 2.5, height / (MENU_LINES) * 1));
	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color(120, 120, 120));
	menu[1].setString("EXIT");
	menu[1].setPosition(sf::Vector2f(20 + (width / 2.5), 50 + (height / (MENU_LINES) * 1)));
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
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem--;
		if (selectedItem < 0)
			selectedItem = MENU_LINES - 1;
		menu[selectedItem].setFillColor(sf::Color::Black);
		menu[selectedItem].setStyle(sf::Text::Bold);
	}
}

void Menu::przesunD()
{
	if (selectedItem >= 0 && selectedItem < MENU_LINES)
	{
		menu[selectedItem].setFillColor(sf::Color(120, 120, 120));
		menu[selectedItem].setStyle(sf::Text::Regular);
		selectedItem++;
		if (selectedItem >= MENU_LINES)
			selectedItem = 0;
		menu[selectedItem].setFillColor(sf::Color::Black);
		menu[selectedItem].setStyle(sf::Text::Bold);
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

	float ySpeed;
	int punkty;

	void idzie();
	void animacja();

public:
	Player();
	sf::FloatRect getGlobalBounds();
	void update(sf::RenderTarget& render, float dt);
	void draw(sf::RenderWindow& window);
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

void Player::idzie() {
	self.setPosition(START_POSITION_X, START_POSITION_Y);
}

void Player::animacja() {
	int predkoscAnimacja = 100 - (int)clock.getElapsedTime().asSeconds();
	float klatkaSzybkosc;
	if (predkoscAnimacja < 30)
		klatkaSzybkosc = 30;
	else
		klatkaSzybkosc = predkoscAnimacja;
	int klatka = zegarAnimacja.getElapsedTime().asMilliseconds() / klatkaSzybkosc;
	int spriteKlatka = SPRITE_WALK_START + klatka;

	if (spriteKlatka > SPRITE_WALK_END) {
		zegarAnimacja.restart();
		spriteKlatka = SPRITE_WALK_START;
	}
	tekstura.loadFromImage(spritesheet, sf::IntRect(spriteKlatka * SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
	sprite.setTexture(tekstura);
	sprite.setScale(sf::Vector2f(4, 4));
	sprite.setOrigin(12.5f, 21);

}

sf::FloatRect Player::getGlobalBounds() {
	return self.getGlobalBounds();
}

void Player::update(sf::RenderTarget& render, float dt) {

	if (zegarPunkty.getElapsedTime().asSeconds() > 1) {
		zegarPunkty.restart();
		punkty += 1;
	}

	punktyTekst.setString("Score: " + std::to_string(punkty));
	animacja();
	idzie();
}

void Player::draw(sf::RenderWindow& window) {
	sprite.setPosition(self.getPosition());
	window.draw(sprite);
	window.draw(punktyTekst);
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

	Player player;
	int menu_selected_flag = 0;
	sf::Clock zegar;
	sf::Clock dtClock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();


			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					myDelay(100);
					menu.przesunG();
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					myDelay(100);
					menu.przesunD();
				}
				if (menu_selected_flag == 0)
				{
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 0)
					{
						//std::cout << "Launching game\n";
						menu_selected_flag = 1;
					}
					if (event.key.code == sf::Keyboard::Enter && menu.getSelectedItem() == 1)
					{
						//std::cout << "Exiting\n";
						menu_selected_flag = 2;
					}
				}
				if (event.key.code == sf::Keyboard::Escape)
				{
					//std::cout << "Back to main menu\n";
					menu_selected_flag = 0;
				}
			}
		}

		window.clear(sf::Color::White);
		if (menu_selected_flag == 0)
			menu.draw(window);
		if (menu_selected_flag == 1)
		{
			sf::Time czas = dtClock.restart();
			float dt = czas.asSeconds();

			player.update(window, dt);
			player.draw(window);
		}
		if (menu_selected_flag == 2)
			exit(0);
		window.display();
	}
	return 0;
}