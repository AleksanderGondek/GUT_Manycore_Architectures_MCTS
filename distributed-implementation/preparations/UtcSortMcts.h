//
// Created by agondek on 12/6/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_UTCSORTMCTS_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_UTCSORTMCTS_H

// 2^16
#define DEFAULT_MESSAGE_SIZE 65536
//65536

#include "MctsNode.h"

bool compareNodesByVisists(const MctsNode &node1, const MctsNode &node2);
int uctSort(NimGameState rootState, int maximumIterations);

#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_UTCSORTMCTS_H
