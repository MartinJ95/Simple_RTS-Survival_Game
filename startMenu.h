#ifndef STARTMENU_H
#define STARTMENU_H

#define WIDTH 1000
#define HEIGHT 800

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


class startMenu
{
private:
    int processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    sf::Text startText;
    sf::Text controlsText;
    sf::Font font;
public:
    startMenu();
    int run();
    ~startMenu();
};

#endif // STARTMENU_H
