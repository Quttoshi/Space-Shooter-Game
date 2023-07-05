#include <SFML/Graphics.hpp>
#include<string.h>
#include"bullet.h"
#include<iostream>

using namespace sf;
using namespace std;

class Player {
public:
	Texture tex;
	Sprite sprite;
	float speed = 0.1;
	int x, y;
	int fireRate = 10; 
	Clock fireClock;
	Bullet bullet;
	int player_health = 3;
	
	Player(string png_path)
	{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x = 340; y = 700;
		sprite.setPosition(x, y);
		sprite.setScale(0.5, 0.5);

		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x = 340; y = 700;
		sprite.setPosition(x, y);
		sprite.setScale(0.5, 0.5);

		player_health = 3;

	}
	
	void move(string s) {
		float delta_x = 0, delta_y = 0;

		if (s == "u")
			delta_y = -3;
		else if (s == "d")
			delta_y = 3;
		else if (s == "l")
			delta_x = -3;
		else if (s == "r")
			delta_x = 3;

		delta_x *= speed;
		delta_y *= speed;

		sprite.move(delta_x, delta_y);


	}

	void fire()
	{
		if (fireClock.getElapsedTime().asMilliseconds() > 1000 / fireRate)
		{
			bullet = Bullet("img/laserRed12.png", sprite.getPosition().x + sprite.getGlobalBounds().width / 2 - 5, sprite.getPosition().y - sprite.getGlobalBounds().height / 2, -10);
			fireClock.restart();
		}
	}

};

