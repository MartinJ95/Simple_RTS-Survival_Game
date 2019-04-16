#include "scoreboard.h"

scoreboard::scoreboard(float score) : window(sf::VideoMode(WIDTH, HEIGHT), "sfml works!"), playerScore(score), playerPosition(5)
{
    window.setFramerateLimit(60);
    font.loadFromFile("arial.ttf");
    std::string line;
    std::ifstream myfile ("leaderboard.txt");
    if(myfile.is_open())
    {
        for (int i = 0; i < 5; i++)
        {
            std::getline(myfile, line);
            playerNames[i].setString(line);
            std::getline(myfile, line);
            playerScores[i].setString(line);
        }
        myfile.close();
    }
    for (int i = 0; i < 5; i++)
    {
        playerNames[i].setFont(font);
        playerNames[i].setPosition(350, 50*(i+1));
        playerScores[i].setFont(font);
        playerScores[i].setPosition(650, 50*(i+1));
    }
    for (int i = 0; i < 5; i++)
    {
        std::string temp = playerScores[i].getString();
        std::stringstream ss;
        ss << temp;
        float temp2;
        ss >> temp2;
        if (playerScore > temp2 && playerPosition > i)
        {
            playerPosition = i;
        }
    }
    if (playerPosition < 5)
    {
        for (int i = 4; i >= playerPosition; i--)
        {
            if (i == playerPosition)
            {
                playerNames[i].setString("");
                std::stringstream ss;
                ss << playerScore;
                std::string temp;
                temp = ss.str();
                playerScores[playerPosition].setString(temp);
            }
            else
            {
                std::string temp;
                temp = playerNames[i-1].getString();
                playerNames[i].setString(temp);
                temp = playerScores[i - 1].getString();
                playerScores[i].setString(temp);
            }
        }
    }
}

void scoreboard::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void scoreboard::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            std::ofstream myfile;
            myfile.open("leaderboard.txt");
            for (int i = 0; i < 5; i++)
            {
                std::string temp;
                temp = playerNames[i].getString();
                myfile << temp << "\n";
                temp = playerScores[i].getString();
                myfile << temp << "\n";
            }
            myfile.close();
        }
        if (event.type == sf::Event::TextEntered && playerPosition < 5)
        {
            std::string name = playerNames[playerPosition].getString();
            if (event.text.unicode == '\b' && name.size() > 0)
            {
                std::string temp;
                temp = playerNames[playerPosition].getString();
                temp.erase(temp.size() - 1, 1);
                playerNames[playerPosition].setString(temp);
            }
            if (event.text.unicode >= 32 && event.text.unicode < 128)
            {
                std::string temp;
                temp = playerNames[playerPosition].getString();
                temp += static_cast<char>(event.text.unicode);
                playerNames[playerPosition].setString(temp);
            }
        }
    }
}

void scoreboard::update()
{

}

void scoreboard::render()
{
    window.clear();
    for (int i = 0; i < 5; i++)
    {
        window.draw(playerNames[i]);
        window.draw(playerScores[i]);
    }
    window.display();
}

scoreboard::~scoreboard()
{

}
