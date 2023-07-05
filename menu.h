#include <SFML/Graphics.hpp>
#include "game.h"
using namespace sf;

class Menu {
public:

    RenderWindow& window;
    Font font;
    Text title;
    Text start_game;
    Text quit;
    Text instructions;
    Text high_score;
    Text instructions_text;
    Text backButton;
    Sprite background; //Game background sprite
    Texture bg_texture;

    Menu(RenderWindow& window) : window(window) {
        // initialize menu attributes here

        // background picture of menu
        bg_texture.loadFromFile("img/b1.jpg");
        background.setTexture(bg_texture);
        background.setScale(0.7, 0.9);

        font.loadFromFile("img/space age.ttf");
        title.setFont(font);
        title.setString("Space Shooter");
        title.setCharacterSize(40);
        title.setPosition(100, 100);

        start_game.setFont(font);
        start_game.setString("Start Game");
        start_game.setCharacterSize(24);
        start_game.setPosition(220, 170);
        start_game.setFillColor(Color::Green);

        instructions.setFont(font);
        instructions.setString("Instructions");
        instructions.setCharacterSize(24);
        instructions.setPosition(210, 210);
        instructions.setFillColor(Color::Green);

        high_score.setFont(font);
        high_score.setString("High Score");
        high_score.setCharacterSize(24);
        high_score.setPosition(225, 250);
        high_score.setFillColor(Color::Green);

        quit.setFont(font);
        quit.setString("Quit");
        quit.setCharacterSize(24);
        quit.setPosition(290, 290);
        quit.setFillColor(Color::Red);

        
    }


    void display_menu() {
        bool showInstructions = false; // to check if instructions button is pressed
        bool showBackButton = false; // to check if Back to Menu button is pressed

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                    exit(0);
                }
                if (event.type == Event::MouseButtonPressed) {
                    if (start_game.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        Game g;
                        g.start_game();
                    }
                    else if (instructions.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        showInstructions = true; // set showInstructions flag to true
                    }
                    else if (high_score.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        // high score
                    }
                    else if (quit.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        window.close();
                        exit(0);
                    }
                    else if (showInstructions && backButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                        showInstructions = false; // return back to menu
                    }
                }
            }

            window.clear(Color::Black);
            if (showInstructions) {
                instructions_text.setFont(font);
                instructions_text.setString("1. Use the arrow keys to move your ship and \n  spacebar to shoot.\n\n"
                    "2. Collect power - ups to upgrade your \n  weapons and abilities.\n\n"
                    "3. Dodge obstacles and enemy fire to avoid \n  losing lives.\n\n"
                    "4. Shoot down enemy ships to earn points.\n\n"
                    "5. Aim for high scores and compete \n  with other players!\n\n");
                instructions_text.setCharacterSize(18);
                instructions_text.setPosition(40, 50);
                instructions_text.setFillColor(Color::White);
                window.draw(instructions_text);

                backButton.setFont(font);
                backButton.setString("Back to Menu");
                backButton.setCharacterSize(24);
                backButton.setPosition(200, 350);
                backButton.setFillColor(Color::Red);
                window.draw(backButton);
            }
            else {
                // Draw the rest of the menu elements
                window.draw(background);
                window.draw(title);
                window.draw(start_game);
                window.draw(instructions);
                window.draw(quit);
                window.draw(high_score);
            }
            window.display();
        }
    }




};
