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
                ChessGameState(unsigned short int lastActivePlayer,
                               std::unordered_map<std::string, std::string> chessBoard);
                ChessGameState clone(void);

                // Important: This needs to be set for ChessGame state to work!
                void setChessBoard(std::unordered_map<std::string, std::string> chessBoard);

                unsigned short int getLastActivePlayer(void);
                void setLastActivePlayer(unsigned short int playerId);

                unsigned long int getStateValue(unsigned short int playerId);
                std::vector<std::string> getAvailableActions(void);
                void performAction(std::string action);

            private:
                std::unordered_map<std::string, std::string> _chessBoard;
                std::vector<std::string> _availableActions;
                unsigned short int _lastActivePlayer;

                bool _playerOneKingDown = false;
                bool _playerTwoKingDown = false;

                std::string GetPieceTypeFromBoardValue(std::string value);
                std::vector<std::string> getAvailableActions(std::string piecePosition,
                                                             std::string pieceData);
                std::vector<std::string> GetKingPossibleMoves(std::string kingPosition,
                                                              std::string kingData);
                std::vector<std::string> GetPawnPossibleMoves(std::string pawnPosition,
                                                              std::string pawnData);
                bool IsBoardFieldEmpty(std::string position);
            };
    }
}

#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_CHESSGAMESTATE_H
