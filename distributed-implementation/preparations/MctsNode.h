//
// Created by agondek on 12/6/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSNODE_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSNODE_H


#include "NimGameState.h"

class MctsNode
{
public:
    MctsNode(int action, MctsNode* parent, NimGameState* state);
    int previousAction;
    int wins;
    int visits;
    std::vector<int> actionsNotTaken;
    std::vector<MctsNode> childNodes;
    int lastActivePlayer;

    MctsNode* parentNode;
    MctsNode* selectNextChildNode(void);
    MctsNode* addChildNode(int action, NimGameState* state);
    void update(int value);
    std::string representation(void);
};


#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSNODE_H
