#include "startMenu.h"

startMenu::startMenu() : window(sf::VideoMode(WIDTH, HEIGHT), "sfml works!")
{
    window.setFramerateLimit(60);
    font.loadFromFile("arial.ttf");
    startText.setFont(font);
    startText.setPosition(450, 300);
    startText.setString("Start");
    controlsText.setFont(font);
    controlsText.setPosition(10, 500);
    controlsText.setString("controls:\npress Q to switch between place and select mode\nwhen in place mode press left mouse button to place down soldier\npress w to switch soldier type\nwhen in select mode left mouse click while mouse over soldier to select\nthen right nouse click to tell them to move wherever the mouse is\nclick start to start");
}

int startMenu::run()
{
    while (window.isOpen())
    {
        if (processEvents() == 1)
        {
            return 1;
        }
        update();
        render();
    }
    return 0;
}

int startMenu::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            return 1;
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (mousePosition.x > startText.getPosition().x && mousePosition.x < startText.getPosition().x + startText.getGlobalBounds().width && mousePosition.y > startText.getPosition().y && mousePosition.y < startText.getPosition().y + startText.getGlobalBounds().height)
                {
                    window.close();
                    return 0;
                }
            }
        }

    }
    return 0;
}

void startMenu::update()
{

}

void startMenu::render()
{
    window.clear();
    window.draw(startText);
    window.draw(controlsText);
    window.display();
}

startMenu::~startMenu()
{

}
