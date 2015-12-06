//
// Created by agondek on 12/6/15.
//

#include <algorithm>
#include <sstream>
#include <vector>
#include "MctsNode.h"

bool compareNodesUcb(const MctsNode &node1, const MctsNode &node2)
{
    int node1key = (int)(node1.wins / node1.visits + sqrt(2 * log(node2.visits / node1.visits)));
    int node2key = (int)(node2.wins / node2.visits + sqrt(2 * log(node1.visits / node2.visits)));
    return (node1key < node2key);
}

std::string prinOutVector(std::vector<int> vect)
{
    std::stringstream buffer;
    for(std::vector<int>::iterator it = vect.begin(); it != vect.end(); ++it)
    {
        buffer << *it << ",";
    }
    return buffer.str();
}

std::string prinOutChildrenNodes(std::vector<MctsNode> vect)
{
    std::stringstream buffer;
    buffer << "(";
    for(std::vector<MctsNode>::iterator it = vect.begin(); it != vect.end(); ++it)
    {
        buffer << "[" << it->previousAction << "]" << ",";
    }
    buffer << ")";
    return buffer.str();
}

MctsNode::MctsNode(int action, MctsNode *parent, NimGameState* state)
{
    this->wins = 0;
    this->visits = 0;

    this->previousAction = action;
    this->parentNode = parent;

    if(state != NULL)
    {
        this->actionsNotTaken = state->getAvailableActions();
        this->lastActivePlayer = state->lastActivePlayer;
    }
}

MctsNode* MctsNode::selectNextChildNode(void)
{
    std::sort(this->childNodes.begin(), this->childNodes.end(), compareNodesUcb);
    return &this->childNodes.back();
}

MctsNode* MctsNode::addChildNode(int action, NimGameState* state)
{
    this->actionsNotTaken.erase(std::remove(this->actionsNotTaken.begin(), this->actionsNotTaken.end(), action), this->actionsNotTaken.end());
    MctsNode newChild(action, this, state);
    this->childNodes.push_back(newChild);
    return &this->childNodes.back();
}

void MctsNode::update(int value)
{
    this->visits +=1;
    this->wins += value;
}

std::string MctsNode::representation(void)
{
    std::stringstream buffer;
    buffer <<
    "[Node]: Wins: " << this->wins
    << "; Visits: " << this->visits
    << "; Previous action: " << this->previousAction
    << "; Last active player: " << this->lastActivePlayer
    << "; Actions not taken: " << prinOutVector(this->actionsNotTaken)
    << "; Children nodes: " << prinOutChildrenNodes(this->childNodes)
    << std::endl;
    return buffer.str();
}