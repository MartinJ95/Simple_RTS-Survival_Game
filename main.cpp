#include <iostream>
#include "game.h"
#include "startMenu.h"
#include <stdlib.h>
#include <time.h>
#include "scoreboard.h"

using namespace std;

int main()
{

    // seed the random
    srand(time(nullptr));

    // makes and runs the start menu
    startMenu StartMenu;
    if (StartMenu.run() == 1)
    {
        return 1;
    }

    // makes and runs the game
    game Game;
    if (Game.run() == 1)
    {
        return 1;
    }

    //makes the leaderboard and passes in the score from the game, then displays the leaderboard
    scoreboard Scoreboard(Game.getScore());
    Scoreboard.run();

    // end of program
    return 0;
}

// TODO
//
//
