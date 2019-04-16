#include "game.h"

game::game() : window(sf::VideoMode(WIDTH, HEIGHT), "sfml works!"), enemySpawnRate(10), timeScored(0.f), waveAmount(0)
{
    window.setFramerateLimit(60);
    font.loadFromFile("arial.ttf");
    survivedTime.setFont(font);
    survivedTime.setPosition(600, 50);
    timeToFail.setFont(font);
    timeToFail.setPosition(400, 400);
}

int game::run()
{
    while(window.isOpen())
    {
        if (processEvents() == 1)
        {
            return 1;
        }
        update();
        render();
    }
    timeScored = timeSurvived.getElapsedTime().asSeconds();
    return 0;
}

void game::place(sf::Vector2i i, int t, int r)
{
    #if DEBUG
    LOG("placeFunctionCalled");
    #endif // DEBUG
    if (Player.getResources() >= 100 + 100*r)
    {
        soldier Soldier(0, i.x, i.y, t);
        playerTroops.push_back(Soldier);
        Player.subtractResources(100 + 100*r);
    }

}

void game::select(sf::Vector2i i)
{
    for (auto &p : playerTroops)
    {
        if (p.getSelected() == true)
        {
            p.deselect();
        }
    }
    for (auto &p : playerTroops)
    {
        if (i.x > p.getx() && i.x < p.getx() + p.getWidth() && i.y > p.gety() && i.y < p.gety() + p.getHeight())
        {
            p.select();
        }
    }
}

int game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            return 1;
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Q)
            {
                Player.changeMode();
            }
            else if (event.key.code == sf::Keyboard::W)
            {
                Player.changeSoldierType();
            }
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (Player.getMode() == 1)
                {
                    #if DEBUG
                    LOG("mouseClicked");
                    #endif // DEBUG
                    place(Player.getMousePosition(), Player.getSoldierType(), Player.getSoldierType());
                }
                else if (Player.getMode() == 0)
                {
                    select(Player.getMousePosition());
                }
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                if (Player.getMode() == 0)
                {
                    for (auto &p : playerTroops)
                    {
                        if (p.getSelected() == true)
                        {
                            p.setDestination(Player.getMousePosition().x, Player.getMousePosition().y);
                        }
                    }
                }
            }
        }
    }
    return 0;
}
void game::update()
{
    if (timeSurvived.getElapsedTime().asSeconds() >= 120)
    {
        enemySpawnRate = 1;
    }
    else if (timeSurvived.getElapsedTime().asSeconds() >= 90)
    {
        enemySpawnRate = 3;
    }
    else if (timeSurvived.getElapsedTime().asSeconds() >= 60)
    {
        enemySpawnRate = 5;
    }
    else if (timeSurvived.getElapsedTime().asSeconds() >= 30)
    {
        enemySpawnRate = 7;
    }
    Player.setMousePosition(sf::Mouse::getPosition(window));
    if (enemySpawner.getElapsedTime().asSeconds() >= enemySpawnRate)
    {
        soldier Soldier(1, rand()%WIDTH - 50, rand()%HEIGHT - 50, 0);
        enemyTroops.push_back(Soldier);
        enemySpawner.restart();
        std::cout << "enemySpawned" << std::endl;
    }
    if (waveTimer.getElapsedTime().asSeconds() >= 10.f)
    {
        for (int i = 0; i < waveAmount; i++)
        {
            soldier Soldier(1, rand()%WIDTH, rand()%HEIGHT - 50, 0);
            enemyTroops.push_back(Soldier);
        }
        waveAmount++;
        waveTimer.restart();
    }
    if (resourceIncome.getElapsedTime().asSeconds() >= 5)
    {
        Player.addResources(50);
        resourceIncome.restart();
    }
    for (auto &p : playerTroops)
    {
        p.move();
    }
    for (auto &p : bullets)
    {
        p.move();
    }
    for (auto &p : bullets)
    {
        if (p.getOwnership() == 0)
        {
            for (auto &e : enemyTroops)
            {
                p.checkCollisionSoldier(e);
            }
        }
        else if (p.getOwnership() == 1)
        {
            for (auto &e : playerTroops)
            {
                p.checkCollisionSoldier(e);
            }
        }
        p.checkOffScreen(window.getSize().x, window.getSize().y);
    }
    if (bullets.size() >= 0)
    {
        for (int i = 0; i < bullets.size(); i++)
        {
            if (bullets[i].isAlive() == false)
            {
                bullets.erase(bullets.begin() + i);
            }
        }
    }
    if (enemyTroops.size() >= 0)
    {
        for (int i = 0; i < enemyTroops.size(); i++)
        {
            if (enemyTroops[i].isAlive() == false)
            {
                enemyTroops.erase(enemyTroops.begin() + i);
            }
        }
    }
    if (playerTroops.size() >= 0)
    {
        for (int i = 0; i < playerTroops.size(); i++)
        {
            if (playerTroops[i].isAlive() == false)
            {
                playerTroops.erase(playerTroops.begin() + i);
            }
        }
    }
    for (auto &p : playerTroops)
    {
        sf::Vector2f currentTarget;
        float currentTargetDistance = 2000;
        for (auto &e : enemyTroops)
        {
            sf::Vector2f distance = e.getPosition() - p.getPosition();
            float distanceLength = sqrt(distance.x * distance.x + distance.y * distance.y);
            if (distanceLength <= currentTargetDistance)
            {
                currentTarget = e.getOrigin();
                currentTargetDistance = distanceLength;
            }
        }
        if (p.shoot() && enemyTroops.size() > 0)
        {
            std::cout << currentTarget.x << "  " << currentTarget.y << std::endl;
            bullet Bullet(p.getOwnership(), p.getOrigin(), currentTarget);
            bullets.push_back(Bullet);
        }
    }
    for (auto &p : enemyTroops)
    {
        sf::Vector2f currentTarget;
        float currentTargetDistance = 2000;
        for (auto e : playerTroops)
        {
            sf::Vector2f distance = e.getPosition() - p.getPosition();
            float distanceLength = sqrt(distance.x * distance.x + distance.y * distance.y);
            if (distanceLength <= currentTargetDistance)
            {
                currentTarget = e.getOrigin();
                currentTargetDistance = distanceLength;
            }
        }
        if (p.shoot() && playerTroops.size() > 0)
        {
            std::cout << currentTarget.x << "  " << currentTarget.y << std::endl;
            bullet Bullet(p.getOwnership(), p.getOrigin(), currentTarget);
            bullets.push_back(Bullet);
        }
    }
}

void game::render()
{
    window.clear();
    Player.draw(window);
    for (auto &p : playerTroops)
    {
        p.draw(window);
    }
    for (auto &p : enemyTroops)
    {
        p.draw(window);
    }
    for (auto &p : bullets)
    {
        p.draw(window);
    }
    std::stringstream ss;
    ss << timeSurvived.getElapsedTime().asSeconds();
    survivedTime.setString("time survived = " + ss.str());
    window.draw(survivedTime);
    if (playerTroops.size() > 0)
    {
        if (failTimerOn == true)
        {
            failTimerOn = false;
        }
    }
    else if (failTimerOn == false)
    {
        failTimerOn = true;
        failTimer.restart();
    }
    else if (failTimer.getElapsedTime().asSeconds() < 11)
    {
        int failing = 10 - failTimer.getElapsedTime().asSeconds();
        std::stringstream ss;
        ss << failing;
        timeToFail.setString("place a unit!! " + ss.str());
        window.draw(timeToFail);
    }
    else
    {
        window.close();
    }
    window.display();
}

float game::getScore()
{
    return timeScored;
}


game::~game()
{

}
