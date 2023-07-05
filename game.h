#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "player.h"
#include "alpha.h"
//#include "beta.h"
//#include "gamma.h"
using namespace sf;
using namespace std;

const char title[] = "OOP-Project, Spring-2023";

class Game {
public:
    Sprite background;
    Texture bg_texture;
    Player* player;
    Alpha* alpha[10];
    //Beta* alpha[10];
    //Gamma* alpha[10];
    int numalpha = 10;
    Clock clock;
    bool moveDown = true; // Variable to keep track of Alpha movement direction
    Bomb* bombs[10];
    Clock dragonClock;


    Game() {
        player = new Player("img/player_ship.png");
        bg_texture.loadFromFile("img/background1.jpg");
        background.setTexture(bg_texture);
        background.setScale(0.7, 0.9);

        // Create 4 alpha with different initial positions
        const int numalpha = 10;
        const float Alpha_POSITIONS[numalpha][2] = {
            {150, 100},
            {250, 100},
            {350, 100},
            {450, 100},
            {550, 100},
            {150, 200},
            {250, 200},
			{350, 200},
			{450, 200},
			{550, 200}
        };

        for (int i = 0; i < numalpha; i++) {
            alpha[i] = new Alpha("img/enemy_1.png");
            alpha[i]->sprite.setPosition(Alpha_POSITIONS[i][0], Alpha_POSITIONS[i][1]);
            bombs[i] = new Bomb("img/ufoRed.png");
        }
    }

    void start_game() {
        srand(time(0));
        RenderWindow window(VideoMode(780, 780), title);

                    int player_health = 3;


        while (window.isOpen()) {
            float time = clock.restart().asSeconds();

            Event e;
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed) {
                    window.close();
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                player->move("l");
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                player->move("r");
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                player->move("u");
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                player->move("d");
            }
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                player->fire();
            }

            // Wrap the player ship around the window
            if (player->sprite.getPosition().x < 0) {
                player->sprite.setPosition(window.getSize().x, player->sprite.getPosition().y);
            }
            else if (player->sprite.getPosition().x > window.getSize().x) {
                player->sprite.setPosition(0, player->sprite.getPosition().y);
            }
            if (player->sprite.getPosition().y < 0) {
                player->sprite.setPosition(player->sprite.getPosition().x, window.getSize().y);
            }
            else if (player->sprite.getPosition().y > window.getSize().y) {
                player->sprite.setPosition(player->sprite.getPosition().x, 0);
            }


            Alpha* collidedalpha[4];
            int count = 0;
            bool destroyed = false;

            if (player->bullet.sprite.getPosition().y < 0) // If bullet goes out of screen
            {
                player->bullet.sprite.setPosition(-100, -100); // Remove bullet from screen
            }
            else if (!destroyed) {
                for (int i = 0; i < numalpha; i++) {
                    if (player->bullet.sprite.getGlobalBounds().intersects(alpha[i]->sprite.getGlobalBounds())) {
                        alpha[i]->health--; // decrement the Alpha's health
                        player->bullet.sprite.setPosition(-100, -100);
                        if (alpha[i]->health == 0) {
                            alpha[i]->sprite.setPosition(rand() % 1000 + 900, 0);
                            alpha[i]->health = 5; // reset the Alpha's health
                        }
                        break;
                    }
                }
            }

            if (!destroyed) {
                player->bullet.move();
            }


            // Move each Alpha up or down and check for collision with player
            for (int i = 0; i < numalpha; i++) {
                if (moveDown) {
                    alpha[i]->sprite.move(0, 50 * time);
                }
                else {
                    alpha[i]->sprite.move(0, -50 * time);
                }
                if (alpha[i]->sprite.getGlobalBounds().intersects(player->sprite.getGlobalBounds())) {
                    // Game over
                    window.close();
                }
            }

            // Change Alpha movement direction if an Alpha has reached the top or bottom of the screen
            if (alpha[0]->sprite.getPosition().y >= 300) {
                moveDown = false;
            }
            else if (alpha[numalpha - 1]->sprite.getPosition().y <= 100) {
                moveDown = true;
            }

            // bombs
            for (int i = 0; i < numalpha; i++) {
                if (rand() % 5000 < 1) { // Drop a bomb with a 0.5% chance
                    bombs[i]->drop(alpha[i]->sprite.getPosition());
                }
                if (bombs[i]->collision(player->sprite)) {
                    player_health--; // Decrement player's health
                    if (player_health == 0) {
                        window.close(); // Game over if player's health reaches zero
                    }
                    bombs[i]->sprite.setPosition(-100, -100); // Remove bomb from screen
                }
            }

            
    
            window.clear(Color::Black);
            window.draw(background);
            window.draw(player->sprite);
            for (int i = 0; i < numalpha; i++) {
                window.draw(alpha[i]->sprite);
                bombs[i]->move(time);
                window.draw(bombs[i]->sprite);
            }
            
            window.draw(player->bullet.sprite);
            window.display();
        }

    }

};
