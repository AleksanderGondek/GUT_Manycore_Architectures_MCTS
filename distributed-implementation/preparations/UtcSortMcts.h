//
// Created by agondek on 12/6/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_UTCSORTMCTS_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_UTCSORTMCTS_H

#include "MctsNode.h"

bool compareNodesByVisists(const MctsNode &node1, const MctsNode &node2);
int uctSort(NimGameState rootState, int maximumIterations);

#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_UTCSORTMCTS_H
