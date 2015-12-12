//
// Created by agondek on 12/12/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_CHESSGAMEPARSER_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_CHESSGAMEPARSER_H

#include "../MctsCommon.h"

namespace Mcts
{
    namespace Parsers
    {
        namespace ChessGame
        {
            std::unordered_map<std::string, std::string> LoadChessBoard(std::string pathToFile);
        }
    }
}

#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_CHESSGAMEPARSER_H
