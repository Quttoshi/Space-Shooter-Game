#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
using namespace sf;
using namespace std;


class Bullet {
public:
    Texture tex;
    Sprite sprite;
    float speed;

    Bullet() {}

    Bullet(string png_path, int x, int y, float spd)
    {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        sprite.setPosition(x, y);
        sprite.setScale(0.3, 0.3);
        speed = spd;
    }

    void move()
    {
        sprite.move(0, speed);
    }
};


