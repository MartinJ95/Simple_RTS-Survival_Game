#ifndef SOLDIER_H
#define SOLDIER_H

#include <SFML/Graphics.hpp>
#include <iostream>

#define SIZE 50

class soldier
{
private:
    int ownership; // 0 = player , 1 = enemy
    int type;
    int lives;
    float reloadTime;
    float speed = 5;
    sf::CircleShape shape;
    bool selected = false;
    sf::Vector2f position;
    sf::Vector2f destination;
    sf::Clock shotLimiter;
    bool alive = true;

public:
    soldier();
    soldier(int i, float x, float y, int t);
    void draw(sf::RenderWindow& window);
    int getOwnership();
    bool getSelected();
    bool isAlive();
    int getWidth();
    int getHeight();
    sf::Vector2f getPosition();
    sf::Vector2f getOrigin();
    int getx();
    int gety();
    void select();
    void deselect();
    void setDestination(float x, float y);
    void setAlive();
    void move();
    /*void operator = (const soldier &S)
    {
        position = S.position;
        destination = S.destination;
        alive = S.alive;
        shotLimiter = S.shotLimiter;
    }*/
    bool shoot();
    ~soldier();
};

#endif // SOLDIER_H
