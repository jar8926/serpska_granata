#include <SFML\Graphics.hpp>
#include <time.h>
#include "windows.h"
#include <list>
#include "plane.h"
#include "rocket.h"
#include "player.h"
using namespace sf;

const int W = 640;
const int H = 480;


void menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuTexture3.loadFromFile("images/333.png");
	aboutTexture.loadFromFile("images/about.png");
	menuBackground.loadFromFile("images/Mountains.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(345, 0);

	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
		if (IntRect(100, 150, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
}


/*class RLS : public plane {
public:
	std::string name;
	plane Plan1;
	RLS(plane *a) {
		Plan1 = *a;
		float t1, x1, t2;
		t1 = sqrt((Plan1.x - 100)*(Plan1.x - 100) + (980 - Plan1.y)*(980 - Plan1.y)) / 0.8;
		x1 = Plan1.x + t1 * Plan1.dx;
		t2 = sqrt((x1 - 100)*(x1 - 100) + (980 - Plan1.y)*(980 - Plan1.y)) / 0.8;
		x = Plan1.x + (t1+t2) * Plan1.dx;
		y = Plan1.y;
		name = "RLS";
		dx = Plan1.dx;
	}
};*/

bool isCollide(Entity *a, Entity *b)
{
	return (b->x - a->x)*(b->x - a->x) +
		(b->y - a->y)*(b->y - a->y) <
		(a->R + b->R)*(a->R + b->R);
}

int main()
 {
	RenderWindow window(sf::VideoMode(W, H), "Menu");
	menu(window);
	srand(time(0));

	RenderWindow app(VideoMode(W, H), "Srpska granata!");
	app.setFramerateLimit(60);

	Image images[8];
	images[0].loadFromFile("images/Explodes.png");
	images[1].loadFromFile("images/A-10.png");
	images[2].loadFromFile("images/RollingPart.png");
	images[3].loadFromFile("images/Missiles.png");
	images[4].loadFromFile("images/Tornado.png");
	images[5].loadFromFile("images/F-18.png");
	images[6].loadFromFile("images/F-16.png");
	images[7].loadFromFile("images/F-117.png");
	for (int i = 0; i < 8; i++) {
		images[i].createMaskFromColor(Color(255, 255, 255));
	}

	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9;
	t6.loadFromFile("images/RLS.png");
	t1.loadFromImage(images[2]);
	t2.loadFromFile("images/Back_Fix.png");
	//t3.loadFromFile("images/Explodes.png");
	t3.loadFromImage(images[0]);
	t4.loadFromImage(images[1]);
	t5.loadFromImage(images[3]);
	t6.loadFromImage(images[4]);
	t7.loadFromImage(images[5]);
	t8.loadFromImage(images[6]);
	t9.loadFromImage(images[7]);
	t1.setSmooth(true);
	t2.setSmooth(true);

	Sprite background(t2);

	Animation sExplosion(t3, 0, 0, 64, 64, 5, 0.6);
	Animation Tornado(t6, 0, 0, 39, 13, 1, 0);
	Animation A10(t4, 0, 0, 53, 13, 1, 0);
	Animation F18(t7, 0, 0, 59, 13, 1, 0);
	Animation F16(t8, 0, 0, 42, 14, 1, 0);
	Animation F117(t9, 0, 0, 76, 13, 1, 0);
	Animation sRocket(t5, 0, 0, 32, 7, 2, 1);
	Animation sPlayer(t1, 0, 0, 65, 13, 1, 0);
	Animation sRls(t6, 0, 0, 64, 64, 16, 0);
	std::list<Entity*> entities;

	player *p = new player();
	p->settings(sPlayer, 42, 413, 0, 20);
	entities.push_back(p);

	int RCount = 0;

	while (app.isOpen())
	{
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape) {
					app.close();
				}

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Space)
				{
					if (RCount < 2) {
						RCount++;
						rocket* b = new rocket();
						b->settings(sRocket, p->x, p->y, p->angle, 10);
						entities.push_back(b);
					}
				}
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle += 1.5;
		if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle -= 1.5;
		if (p->angle > -9) p->angle = -9;
		if (p->angle < -90) p->angle = -90;
		else p->thrust = false;
		

		for (auto a : entities)
			for (auto b : entities)
			{
				if (a->name == "plane" && b->name == "rocket")
					if (isCollide(a, b))
					{
						a->life = false;
						b->life = false;
						Entity *e = new Entity();
						e->settings(sExplosion, a->x, a->y);
						e->name = "explosion";
						entities.push_back(e);
					}
			}

		for (auto b : entities) {
			if ((b->name == "rocket") && ((b->x <= 0) || (b->x >= W) || (b->y <= 0) || (b->y >= H))) {
				b->life = false;
			}
		}

		for (auto b : entities) {
			if (b->name == "rocket") {
				if (Keyboard::isKeyPressed(Keyboard::Up)) b->angle -= 1;
				if (Keyboard::isKeyPressed(Keyboard::Down))  b->angle += 1;
			}
			if ((b->name == "rocket") && (b->life == false)) {
				RCount--;
			}
		}

		p->anim = sPlayer;


		for (auto e : entities)
			if (e->name == "explosion")
				if (e->anim.isEnd()) e->life = 0;

		if (rand() % 80 == 0)
		{
			int a = rand() % 3;
			if (a == 0) {
				plane *a = new plane();
				a->settings(A10, W, rand() % H - 125 + 15, 0, 25);
				entities.push_back(a);
			}
			else if (a == 1) {
				plane *a = new plane();
				a->settings(Tornado, W, rand() % H - 125 + 15, 0, 25);
				entities.push_back(a);
			}
			else if (a == 2) {
				plane *a = new plane();
				a->settings(F18, W, rand() % H - 125 + 15, 0, 25);
				entities.push_back(a);
			}
			else if (a == 3) {
				plane *a = new plane();
				a->settings(F16, W, rand() % H - 125 + 15, 0, 25);
				entities.push_back(a);
			}
		}

		if (rand() % 1000 == 0) {
			plane *a = new plane();
			a->settings(F117, W, rand() % H - 125 + 15, 0, 25);
			entities.push_back(a);
		}

		for (auto i = entities.begin(); i != entities.end();)
		{
			Entity *e = *i;

			e->update();
			e->anim.update();

			if (e->life == false) { i = entities.erase(i); delete e; }
			else i++;
		}

		app.draw(background);
		for (auto i : entities) i->draw(app);
		app.display();
	}

	return 0;
}
