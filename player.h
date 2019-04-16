#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/graphics.hpp>
#include <iostream>
#include <sstream>

#define DEBUG 0

#define LOG(x) std::cout << x << std::endl

class player
{
private:
    int mode = 1; // 0 = select mode , 1 = place mode
    int soldierType = 0;
    int resources = 100;
    sf::Vector2i mousePosition;
    sf::Text resourceText;
    sf::Text modeText;
    sf::Font font;

public:
    player();
    void addResources(int i);
    void subtractResources(int i);
    void changeMode();
    void changeSoldierType();
    void setMousePosition(sf::Vector2i i);
    int getResources();
    int getMode();
    int getSoldierType();
    sf::Vector2i getMousePosition();
    void draw(sf::RenderWindow &window);
    ~player();


};

#endif // PLAYER_H
