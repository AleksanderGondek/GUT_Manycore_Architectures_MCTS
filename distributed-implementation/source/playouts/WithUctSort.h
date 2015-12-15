//
// Created by agondek on 12/12/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_PLAYOUTS_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_PLAYOUTS_H

#include "../MctsCommon.h"
#include "../games/IGameState.h"
#include "../tree/Node.h"
#include "../tree/Serializer.h"
#include "../tree/Deserializer.h"
#include "../tree/Merger.h"
#include "../utils/ChessBoardRepresentations.h"

namespace Mcts
{
    namespace Playouts
    {
        std::string getBestMoveUsingUtcSort(Mcts::GameStates::IGameState* rootState,
                                            int maximumIterations,
                                            bool useParallelization);
    }
}

#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_PLAYOUTS_H
