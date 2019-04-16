#include "bullet.h"

bullet::bullet(int i, sf::Vector2f p, sf::Vector2f d) : ownership(i), position(p), destination(d), shape(SIZE)
{
    shape.setPosition(position.x - SIZE, position.y - SIZE);
    position.x = position.x - SIZE;
    position.y = position.y - SIZE;
    destination.x -= SIZE;
    destination.y -= SIZE;
    destination += (destination - position)*10.f;
    shape.setFillColor(sf::Color::Red);
}

sf::Vector2f bullet::getPosition()
{
    return position;
}

int bullet::getOwnership()
{
    return ownership;
}

bool bullet::isAlive()
{
    return alive;
}

void bullet::setAlive()
{
    alive = false;
}

void bullet::checkCollisionSoldier(soldier &target)
{
    if (position.x >= target.getPosition().x && position.x <= target.getPosition().x + target.getWidth() && position.y >= target.getPosition().y && position.y <= target.getPosition().y + target.getHeight())
    {
        target.setAlive();
        setAlive();
    }
}

void bullet::checkOffScreen(int w, int h)
{
    if (position.x < 0 || position.x > w || position.y < 0|| position.y > h)
    {
        setAlive();
    }
}

void bullet::move()
{
    sf::Vector2f movement = destination - position;

    if (movement.x != 0 || movement.y != 0)
    {
        float length = sqrt(movement.x * movement.x + movement.y * movement.y);
        if (length < 1)
        {
            return;
        }
        movement.x = movement.x/length;
        movement.y = movement.y/length;
    }

    if (movement.x > 0)
    {
        if (destination.x - position.x > speed)
        {
            position.x += movement.x *speed;
        }
        else
        {
            position.x += movement.x;
        }
    }
    else if (movement.x < 0)
    {
        if (destination.x - position.x < -speed)
        {
            position.x += movement.x *speed;
        }
        else
        {
            position.x += movement.x;
        }
    }
    if (movement.y > 0)
    {
        if (destination.y - position.y > speed)
        {
            position.y += movement.y *speed;
        }
        else
        {
            position.y += movement.y;
        }
    }
    else if (movement.y < 0)
    {
        if (destination.y - position.y < -speed)
        {
            position.y += movement.y *speed;
        }
        else
        {
            position.y += movement.y;
        }
    }
    shape.setPosition(position.x, position.y);
}

void bullet::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

bullet::~bullet()
{

}
