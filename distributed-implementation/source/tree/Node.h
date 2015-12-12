//
// Created by agondek on 12/12/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_NODE_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_NODE_H

#include "../MctsCommon.h"
#include "../games/NimGameState.h"

namespace Mcts
{
    namespace Tree
    {
        bool compareTwoNodesWithUcb(Node &node1, Node &node2);

        class Node
        {
            public:
                Node(std::string action, Node* parent, GameStates::NimGameState* state);

                std::vector<std::string> actionsNotTaken;
                std::vector<Node> childNodes;

                Node* getParentNode(void);
                std::string getPreviousAction(void);
                unsigned short int getLastActivePlayer(void);
                void setLastActivePlayer(unsigned short int playerId);
                unsigned long int getWins(void);
                void adjustWins(unsigned long int wins);
                unsigned long int getVisits(void);
                void adjustVisits(unsigned long int visits);

                Node* selectNextChildNode(void);
                Node* addChildNode(std::string action, GameStates::NimGameState* state);

                void update(unsigned long int value);
            private:
                Node*_parentNode;
                std::string _previousAction;
                unsigned short int _lastActivePlayer;
                unsigned long int _wins;
                unsigned long int _visits;
        };
    }
}

#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_NODE_H
