#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "soldier.h"

#define SIZE 10

class bullet
{
private:
    int speed = 10;
    int ownership; // 0 = player , 1 = enemy
    sf::Vector2f position;
    sf::Vector2f destination;
    sf::CircleShape shape;
    bool alive = true;
public:
    bullet(int i, sf::Vector2f p, sf::Vector2f d);
    sf::Vector2f getPosition();
    int getOwnership();
    bool isAlive();
    void setAlive();
    void checkCollisionSoldier(soldier &target);
    void checkOffScreen(int w, int h);
    void move();
    void draw(sf::RenderWindow& window);
    ~bullet();
};

#endif // BULLET_H
