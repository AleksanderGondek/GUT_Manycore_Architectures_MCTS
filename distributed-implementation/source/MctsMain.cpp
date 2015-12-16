//
// Created by agondek on 12/12/15.
//

#include "MctsCommon.h"
#include "games/NimGameState.h"
#include "games/ChessGameState.h"
#include "playouts/WithUctSort.h"

#include "parsers/ChessGameParser.h"
#include "utils/ChessBoardRepresentations.h"

int main(int argc, char* argv[])
{
    // Parse arguments
    // First param is the name of the program being run
    // (due to call: mpirun -np 2 program-name

//    tmp bs
    std::unordered_map<std::string, std::string> test =
            Mcts::Parsers::ChessGame::LoadChessBoard(
                    "/home/agondek/GUT/GUT_Manycore_Architectures_MCTS/distributed-implementation/example_input.txt");
    Mcts::GameStates::ChessGameState gameState(2, test);

    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // IMPORTANT!: if number of _chips mod (k + 1) == 0, second player should win (optimal)
    // Where k is the maximum number of _chips allowed to draw at once
    // Uncomment to present a valid game
    // Mcts::GameStates::NimGameState gameState(2,400);
    // Mcts::GameStates::NimGameState gameState(MCTS_PLAYER_TWO_ID, 400);

    bool allProcFinished = false;
    bool finished = false;
    int rcv_buff[2 * world_size];
    int ctr = 0;
    while (!gameState.getAvailableActions().empty() || !allProcFinished)
    {
        if(world_rank == 0)
        {
            std::cout << "Board before taking move:" << std::endl;
            std::cout << gameState.getGameRepresentation() << std::endl;
        }

        std::string action;
        if (gameState.getLastActivePlayer() == MCTS_PLAYER_ONE_ID)
        {
            // Last player was no 1, so it's player 2 turn
            action = Mcts::Playouts::getBestMoveUsingUtcSort(&gameState, 20, false, finished);
        }
        else
        {
            // Last player was no 2 so it's player 1 turn
            action = Mcts::Playouts::getBestMoveUsingUtcSort(&gameState, 20, true, finished);
        }

        if(world_rank == 0)
        {
            std::cout << "Player: " << 3 - gameState.getLastActivePlayer() << " takes his best move: " << action <<
            std::endl;
        }

        if(action != MCTS_ACTION_NOT_AVAILABLE && !finished)
        {
            gameState.performAction(action);
            if(world_rank == 0)
            {
                std::cout << "Board after taking move:" << std::endl;
                std::cout << gameState.getGameRepresentation() << std::endl;
            }
        }


//        ctr++;
//        allProcFinished = ctr == 100;
        finished = gameState.getAvailableActions().empty();
        allProcFinished = finished;
        //Hax
//        finished = gameState.getAvailableActions().empty();
//        int toSend[1];
//        toSend[0] = finished;
//        //std::cout << "proc " << world_rank << "before all" << std::endl;
//        MPI_Allgather(toSend, 1, MPI::INT,
//                      rcv_buff, 1, MPI::INT,
//                      MPI_COMM_WORLD);
//        //std::cout << "proc " << world_rank << "after all" << std::endl;
//        allProcFinished = true;
//        for(int z = 0; z < (1 * world_size); z++)
//        {
//            allProcFinished = allProcFinished && rcv_buff[z];
//        }
    }

    if(world_rank == 0)
    {
        if (gameState.getStateValue(gameState.getLastActivePlayer()) == MCTS_PLAYER_ONE_ID)
        {
            std::cout << gameState.getLastActivePlayer() << " wins" << std::endl;
        }
        else
        {
            std::cout << 3 - gameState.getLastActivePlayer() << " wins" << std::endl;
        }
    }
    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}
