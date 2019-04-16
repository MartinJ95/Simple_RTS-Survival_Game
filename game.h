#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "player.h"
#include "soldier.h"
#include "bullet.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sstream>

#define WIDTH 1000
#define HEIGHT 800

#define DEBUG 1

#define LOG(x) std::cout << x << std::endl

class game
{
private:
    int processEvents();
    void update();
    void render();
    void place(sf::Vector2i i, int t, int r);
    void select(sf::Vector2i i);

    sf::Clock enemySpawner;
    sf::Clock waveTimer;
    sf::Clock resourceIncome;
    sf::Clock timeSurvived;
    sf::Clock failTimer;
    int waveAmount;
    int enemySpawnRate;
    bool failTimerOn = false;
    float timeScored;
    sf::Font font;
    sf::Text survivedTime;
    sf::Text timeToFail;
    sf::RenderWindow window;
    player Player;
    std::vector<soldier>playerTroops;
    std::vector<soldier>enemyTroops;
    std::vector<bullet>bullets;
public:
    game();
    int run();
    float getScore();
    ~game();

};


#endif // GAME_H
