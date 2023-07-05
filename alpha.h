#include <SFML/Graphics.hpp>
#include<string.h>
#include"invader.h"
using namespace sf;
using namespace std;

class Alpha : public Invader {
public:

    Alpha() {}

    Alpha(string png_path) {
        string filename;
        texture.loadFromFile(png_path);
        sprite.setTexture(texture);
        // set initial position, size, and other properties for the sprite

        sprite.setPosition(x, y);
        sprite.setScale(0.5, 0.5);

        texture.loadFromFile(filename);
        sprite.setTexture(texture);
        sprite.setScale(0.5, 0.5);
        health = 5; // initialize health to 5
    }

};



