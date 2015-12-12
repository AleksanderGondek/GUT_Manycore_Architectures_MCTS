//
// Created by agondek on 12/12/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_CHESSBOARDREPRESENTATIONA_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_CHESSBOARDREPRESENTATIONA_H

#include "../MctsCommon.h"

namespace Mcts
{
    namespace Utils
    {
        namespace ChessBoardRepresentations
        {
            std::string ChessBoardRepresentations(std::unordered_map<std::string, std::string> chessBoard);
            void PrintOutChessBoard(std::unordered_map<std::string, std::string> chessBoard);
        };
    }
}

#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_CHESSBOARDREPRESENTATIONA_H
