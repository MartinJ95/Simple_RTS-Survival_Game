#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#define WIDTH 1000
#define HEIGHT 800

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>

class scoreboard
{
private:
    void processEvents();
    void update();
    void render();
    sf::RenderWindow window;
    float playerScore;
    int playerPosition;
    sf::Font font;
    sf::Text playerNames[5];
    sf::Text playerScores[5];
public:
    scoreboard(float score);
    void run();
    ~scoreboard();
};

#endif // SCOREBOARD_H
