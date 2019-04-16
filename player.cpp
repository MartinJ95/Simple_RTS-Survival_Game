#include "player.h"

player::player()
{
    font.loadFromFile("arial.ttf");
    resourceText.setFont(font);
    resourceText.setPosition(50, 50);
    modeText.setFont(font);
    modeText.setPosition(400, 50);
};

void player::addResources(int i)
{
    resources += i;
};

void player::subtractResources(int i)
{
    resources -= i;
}

void player::changeMode()
{
    if ((mode == 1) ? mode = 0 : mode = 1);
}

void player::changeSoldierType()
{
    if (soldierType < 4)
    {
        soldierType ++;
    }
    else
    {
        soldierType = 0;
    }
}

void player::setMousePosition(sf::Vector2i i)
{
    mousePosition = i;
    #if DEBUG
    LOG(mousePosition.x);
    LOG(mousePosition.y);
    #endif // DEBUG
}

int player::getResources()
{
    return resources;
}

int player::getMode()
{
    return mode;
}

int player::getSoldierType()
{
    return soldierType;
}

sf::Vector2i player::getMousePosition()
{
    return mousePosition;
}

void player::draw(sf::RenderWindow &window)
{
    std::stringstream ss;
    ss << resources;
    resourceText.setString("resources = " + ss.str());
    window.draw(resourceText);
    std::string temp;
    if (soldierType == 0)
    {
        temp = "basic unit - 100 resources";
    }
    else if (soldierType == 1)
    {
        temp = "advanced unit - 200 resources";
    }
    else if (soldierType == 2)
    {
        temp = "super unit - 300 resources";
    }
    else if (soldierType == 3)
    {
        temp = "mega unit - 400 resources";
    }
    else if (soldierType == 4)
    {
        temp = "ultra unit - 500 resources";
    }
    if (mode == 1)
    {
        modeText.setString("place\n" + temp);
    }
    else if (mode == 0)
    {
        modeText.setString("Select");
    }
    window.draw(modeText);
}

player::~player()
{

}
