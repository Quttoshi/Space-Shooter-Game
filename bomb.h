#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
using namespace sf;
using namespace std;

class Bomb {
public:
    Sprite sprite;
    Texture texture;

    Bomb(string filename) {
        texture.loadFromFile(filename);
        sprite.setTexture(texture);
        sprite.setScale(0.2, 0.2);
    }

    void drop(Vector2f position) {
        sprite.setPosition(position);
    }

    void move(float time) {
        sprite.move(0, 100 * time);
    }

    bool collision(Sprite& playerSprite) {
        return sprite.getGlobalBounds().intersects(playerSprite.getGlobalBounds());
    }

};
