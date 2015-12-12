//
// Created by agondek on 11/24/15.
//

#include <iostream>
#include <vector>
#include <mpi.h>
#include "UtcSortMcts.h"

int main2(int argc, char* argv[])
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // IMPORTANT!: if number of _chips mod (k + 1) == 0, second player should win (optimal)
    // Where k is the maximum number of _chips allowed to draw at once
    // Uncomment to present valdi game
    //NimGameState gameState(2,400);
    NimGameState gameState(2, 200);

    while (!gameState.getAvailableActions().empty())
    {
        if(world_rank == 0)
        {
            std::cout << "Main Game State: " << gameState.representation() << std::endl;
        }

        int action = 0;
        if (gameState.lastActivePlayer == 1)
        {
            // Last player was no 1, so it's player 2 turn
            action = uctSort(gameState, 10, false);
        }
        else
        {
            // Last player was no 2 so it's player 1 turn
            action = uctSort(gameState, 10, true);
        }

        if(world_rank == 0)
        {
            std::cout << "Player: " << 3 - gameState.lastActivePlayer << " takes his best move: " << action <<
            std::endl;
        }
        gameState.performAction(action);
    }

    if(world_rank == 0)
    {
        if (gameState.getValue(gameState.lastActivePlayer) == 1)
        {
            std::cout << gameState.lastActivePlayer << " wins" << std::endl;
        }
        else
        {
            std::cout << 3 - gameState.lastActivePlayer << " wins" << std::endl;
        }
    }
    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}
