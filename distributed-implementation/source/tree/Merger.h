//
// Created by agondek on 12/12/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_MERGER_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_MERGER_H

#include "../MctsCommon.h"
#include "Node.h"

namespace Mcts
{
    namespace Tree
    {
        namespace Merger
        {
            void IncorporateRemoteNodeToLocal(Mcts::Tree::Node* local, Mcts::Tree::Node* remote);
        };
    }
}


#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_MERGER_H
