#include "menu.h"
using namespace sf;

int main()
{

    RenderWindow window(VideoMode(650, 500), "Space Shooter");
    Menu menu(window);

    menu.display_menu();


    return 0;
}







