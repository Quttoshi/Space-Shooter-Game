#include <SFML/Graphics.hpp>
#include<string.h>
#include"bomb.h"
#include"enemy.h"
using namespace sf;
using namespace std;

class Dragon : public Enemy {
public:
    
    Dragon() {}

    float speed = 2.0f;
    float direction_x = 1.0f;
    float direction_y = 1.0f;


    Dragon(string png_path) {
        texture.loadFromFile(png_path);
        sprite.setTexture(texture);
        sprite.setScale(0.5f, 0.5f);
        health = 20; // set the health of the dragon
    }

    void move() {
        // Update the position of the dragon based on its current direction and speed
        x += direction_x * speed;
        y += direction_y * speed;

        // Reverse the direction of the dragon if it hits the window boundaries
        if (x < 0 || x > 800 - sprite.getGlobalBounds().width) {
            direction_x *= -1;
        }
        if (y < 0 || y > 600 - sprite.getGlobalBounds().height) {
            direction_y *= -1;
        }

        // Update the position of the sprite
        sprite.setPosition(x, y);
    }
};





