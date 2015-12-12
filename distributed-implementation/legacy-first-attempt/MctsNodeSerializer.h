//
// Created by agondek on 12/6/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSNODESERIALIZER_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSNODESERIALIZER_H

#include <iostream>
#include "MctsNode.h"

namespace MctsNodeSerializer
{
    std::string Serialize(MctsNode node);
};


#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSNODESERIALIZER_H
