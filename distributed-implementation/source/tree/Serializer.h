//
// Created by agondek on 12/12/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_SERIALIZER_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_SERIALIZER_H

#include "../MctsCommon.h"
#include "Node.h"

namespace Mcts
{
    namespace Tree
    {
        namespace Serialization
        {
            std::string SerializeActionsNotTaken(std::vector<std::string> actionsNotTaken);
            std::string Serialize(Mcts::Tree::Node node);
        };
    }
}

#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_SERIALIZER_H
