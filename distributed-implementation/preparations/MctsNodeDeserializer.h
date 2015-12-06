//
// Created by agondek on 12/6/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSNODEDESERIALIZER_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSNODEDESERIALIZER_H

#include <iostream>
#include "MctsNode.h"

namespace MctsNodeDeserializer
{
    MctsNode Deserialize(std::string payload);
};


#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSNODEDESERIALIZER_H
