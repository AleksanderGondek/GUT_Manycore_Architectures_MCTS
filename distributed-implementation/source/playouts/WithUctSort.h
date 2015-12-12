//
// Created by agondek on 12/12/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_PLAYOUTS_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_PLAYOUTS_H

#include "../MctsCommon.h"
#include "../games/NimGameState.h"
#include "../tree/Node.h"
#include "../tree/Serializer.h"
#include "../tree/Deserializer.h"
#include "../tree/Merger.h"

namespace Mcts
{
    namespace Playouts
    {
        std::string getBestMoveUsingUtcSort(Mcts::GameStates::NimGameState rootState,
                                            int maximumIterations);
    }
}

#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_PLAYOUTS_H
