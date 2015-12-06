//
// Created by agondek on 11/24/15.
//

#include <iostream>
#include <vector>
#include "UtcSortMcts.h"

int main(int argc, char* argv[])
{
    // IMPORTANT!: if number of chips mod 4 == 0, second player should win (optimal)
    // Uncomment to present valdi game
    // NimGameState gameState(2,400);

    NimGameState gameState(2,12);
    uctSort(gameState, 5);

    return 0;
    while(!gameState.getAvailableActions().empty())
    {
        std::cout<< "Main Game State: " << gameState.representation() << std::endl;

        int action = 0;
        if(gameState.lastActivePlayer == 1)
        {
            // Last player was no 1, so it's player 2 turn
            action = uctSort(gameState, 100);
        }
        else
        {
            // Last player was no 2 so it's player 1 turn
            action = uctSort(gameState, 1000);
        }

        std::cout<< "Player: " << 3 - gameState.lastActivePlayer << " takes his best move: " << action << std::endl;
        gameState.performAction(action);
    }

    if(gameState.getValue(gameState.lastActivePlayer) == 1)
    {
        std::cout<< gameState.lastActivePlayer << " wins" << std::endl;
    }
    else
    {
        std::cout<< 3 - gameState.lastActivePlayer << " wins" << std::endl;
    }

    return 0;
}
