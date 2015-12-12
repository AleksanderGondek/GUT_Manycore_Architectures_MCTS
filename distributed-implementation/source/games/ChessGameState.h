//
// Created by agondek on 12/12/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_CHESSGAMESTATE_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_CHESSGAMESTATE_H

#include "../MctsCommon.h"

namespace Mcts
{
    namespace GameStates
    {
        class ChessGameState
        {
            public:
                ChessGameState(unsigned short int lastActivePlayer);
                ChessGameState clone(void);

                void setChessBoard(std::unordered_map<std::string, std::string> chessBoard);

                unsigned short int getLastActivePlayer(void);
                void setLastActivePlayer(unsigned short int playerId);

                unsigned long int getStateValue(unsigned short int playerId);
                std::vector<std::string> getAvailableActions(void);
                void performAction(std::string action);

            private:
                std::unordered_map<std::string, std::string> _chessBoard;
                unsigned short int _lastActivePlayer;
            };
    }
}

#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_CHESSGAMESTATE_H
