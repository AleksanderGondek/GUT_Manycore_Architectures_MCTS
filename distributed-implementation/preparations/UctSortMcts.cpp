//
// Created by agondek on 12/6/15.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include "MctsNode.h"
#include "MctsNodeSerializer.h"

bool compareNodesByVisists(const MctsNode &node1, const MctsNode &node2)
{
    return (node1.visits < node2.visits);
}

int uctSort(NimGameState rootState, int maximumIterations)
{
    MctsNode root(0, NULL, &rootState);
    for(int i=0; i<maximumIterations; i++)
    {
        MctsNode* node = &root;
        NimGameState state = rootState.clone();

        // std::cout<< "Copy Repr " << node->representation() << std::endl;

        while(node->actionsNotTaken.empty() && !node->childNodes.empty())
        {
            // std::cout<< "Entering Selection Step" << std::endl;
            node = node->selectNextChildNode();
            state.performAction(node->previousAction);
        }

        if(!node->actionsNotTaken.empty())
        {
            // std::cout<< "Entering Expansion Step" << std::endl;
            std::random_shuffle(node->actionsNotTaken.begin(), node->actionsNotTaken.end());
            int action = node->actionsNotTaken.back();
            // std::cout<< "Action: " << action << std::endl;

            state.performAction(action);
            // std::cout<< state.representation() << std::endl;

            node = node->addChildNode(action, &state);
            // std::cout<< node->representation() << std::endl;
        }

        while(!state.getAvailableActions().empty())
        {
            // std::cout<< "Entering Simulation Step" << std::endl;
            std::random_shuffle(node->actionsNotTaken.begin(), node->actionsNotTaken.end());
            int action = node->actionsNotTaken.back();
            state.performAction(action);
        }

        while(node->parentNode != NULL)
        {
            // std::cout<< "Entering Backpropagation Step" << std::endl;
            node->update(state.getValue(node->lastActivePlayer));
            node = node->parentNode;
        }

        //std::cout << root.representation()<< std::endl;
        std::string test = MctsNodeSerializer::Serialize(root);
        //std::cout << "SEX" << std::endl;
        std::cout << test << std::endl;
    }

    std::sort(root.childNodes.begin(), root.childNodes.end(), compareNodesByVisists);
    MctsNode lastItem = root.childNodes.back();

    // std::cout<< "Root @exit: "<< root.representation() << std::endl;
    // std::cout<< "RootState @exit: "<< rootState.representation() << std::endl;
    return lastItem.previousAction;
}