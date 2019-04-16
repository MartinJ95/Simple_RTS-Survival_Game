#include "soldier.h"

soldier::soldier()
{

}

soldier::soldier(int i, float x, float y, int t) : shape(SIZE) , type(t)
{
    lives = type;
    ownership = i;
    reloadTime = 1.f - 0.2f*type;
    shape.setPosition(x - SIZE, y - SIZE);
    position.x = x - SIZE;
    position.y = y - SIZE;
    destination = position;
    if (ownership == 0)
    {
        shape.setFillColor(sf::Color::Green);
    }
    else if (ownership == 1)
    {
        shape.setFillColor(sf::Color::Yellow);
    }
}

void soldier::draw(sf::RenderWindow& window)
{
    window.draw(shape);
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(position.x + SIZE, position.y + SIZE)),
        sf::Vertex(sf::Vector2f(destination.x + SIZE, destination.y + SIZE))
    };
    window.draw(line, 2, sf::Lines);
}

int soldier::getOwnership()
{
    return ownership;
}

bool soldier::getSelected()
{
    return selected;
}

bool soldier::isAlive()
{
    return alive;
}

int soldier::getWidth()
{
    return shape.getGlobalBounds().height;
}

int soldier::getHeight()
{
    return shape.getGlobalBounds().width;
}

sf::Vector2f soldier::getPosition()
{
    return position;
}

sf::Vector2f soldier::getOrigin()
{
    sf::Vector2f origin = position;
    origin.x += SIZE;
    origin.y += SIZE;
    return origin;
}

int soldier::getx()
{
    return position.x;
}

int soldier::gety()
{
    return position.y;
}

void soldier::select()
{
    selected = true;
}

void soldier::deselect()
{
    selected = false;
}

void soldier::setDestination(float x, float y)
{
    destination.x = x - SIZE;
    destination.y = y - SIZE;
}

void soldier::setAlive()
{
    if (lives == 0)
    {
        alive = false;
    }
    else
    {
        lives --;
    }
}

void soldier::move()
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

bool soldier::shoot()
{
    if (shotLimiter.getElapsedTime().asSeconds() >= reloadTime)
    {
        shotLimiter.restart();
        return true;
    }
    else
    {
        return false;
    }
}

soldier::~soldier()
{

}
