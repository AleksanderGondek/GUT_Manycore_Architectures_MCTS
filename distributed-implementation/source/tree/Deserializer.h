//
// Created by agondek on 12/12/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_DESERIALIZER_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_DESERIALIZER_H

#include "../MctsCommon.h"
#include "Node.h"

namespace Mcts
{
    namespace Tree
    {
        namespace Deserialization
        {
            unsigned long GetIndexOfFirstNthElementInString(std::string text, char characterToFind, int n);
            unsigned long GetIndexOfLastNthElementInString(std::string text, char characterToFind, int n);

            Mcts::Tree::Node Deserialize(std::string payload);
        }
    }
};


#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_DESERIALIZER_H
