//
// Created by agondek on 12/6/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSTREEMERGER_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSTREEMERGER_H


#include "MctsNode.h"

namespace MctsTreeMerger
{
    void MergeTrees(MctsNode* local, MctsNode* remote);
};


#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSTREEMERGER_H
