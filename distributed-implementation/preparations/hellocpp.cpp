//
// Created by agondek on 11/24/15.
//

#include "hellocpp.h"
// #include <mpi.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class NimGameState
{
    public:
        int lastActivePlayer;
        int chips;

        NimGameState(int lastActivePlayer, int chips);

        NimGameState clone(void);
        void performAction(int action);
        std::vector<int> getAvailableActions(void);
        int getValue(int playerId);
        std::string representation(void);
};

NimGameState::NimGameState(int lastActivePlayer, int chips)
{
    this->lastActivePlayer = lastActivePlayer;
    this->chips = chips;
}

NimGameState NimGameState::clone(void)
{
    NimGameState deepClone(this->lastActivePlayer, this->chips);
    return deepClone;
}

void NimGameState::performAction(int action)
{
    this->chips -= action;
    this->lastActivePlayer = 3 - this->lastActivePlayer;
}

std::vector<int> NimGameState::getAvailableActions(void)
{
    std::vector<int> actions;
    if(this->chips > 0)
    {
        for(int i=1; i<std::min(4,(this->chips+1)); i++) //TODO: Why plus 1
        {
            actions.push_back(i);
        }
    }

    return actions;
}

std::string NimGameState::representation(void)
{
    std::stringstream buffer;
    buffer << "Last active player: " << this->lastActivePlayer << "; Chips: " << this->chips << std::endl;
    return buffer.str();
}

int NimGameState::getValue(int playerId)
{
    if(this->lastActivePlayer == playerId)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

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
        std::string representation();
};

bool compareShit(const MctsNode& node1, const MctsNode& node2)
{
    int node1key = (int)(node1.wins / node1.visits + sqrt(2 * log(node2.visits / node1.visits)));
    int node2key = (int)(node2.wins / node2.visits + sqrt(2 * log(node1.visits / node2.visits)));
    return (node1key < node2key);
}

bool compareShit2(const MctsNode& node1, const MctsNode& node2)
{
    return (node1.visits < node2.visits);
}

std::string prinOutVector(std::vector<int> vect)
{
    std::stringstream buffer;
    for(std::vector<int>::iterator it = vect.begin(); it != vect.end(); ++it)
    {
        buffer << *it;
    }
    return buffer.str();
}

MctsNode::MctsNode(int action, MctsNode *parent, NimGameState* state)
{
    this->wins = 0;
    this->visits = 0;

    this->previousAction = action;
    this->parentNode = parent;

    this->actionsNotTaken = state->getAvailableActions();
    this->lastActivePlayer = state->lastActivePlayer;
}

MctsNode* MctsNode::selectNextChildNode(void)
{
    std::sort(this->childNodes.begin(), this->childNodes.end(), compareShit);
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
    << std::endl;
    return buffer.str();
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
    }

    std::sort(root.childNodes.begin(), root.childNodes.end(), compareShit2);
    MctsNode lastItem = root.childNodes.back();

    // std::cout<< "Root @exit: "<< root.representation() << std::endl;
    // std::cout<< "RootState @exit: "<< rootState.representation() << std::endl;
    return lastItem.previousAction;
}

int main(int argc, char* argv[])
{
    // Initialize the MPI environment
    //MPI::Init(argc, argv);

    // Get the number of processes
    //int world_size = MPI::COMM_WORLD.Get_size();

    // Get the rank of the process
    //int world_rank = MPI::COMM_WORLD.Get_rank();

    // Get the name of the processor
    //char processor_name[MPI::MAX_PROCESSOR_NAME];
    //int name_len;
    //MPI::Get_processor_name(processor_name, name_len);

    // IMPORTANT!: if number of chips mod 4 == 0, second player should win (optimal)
    NimGameState gameState(2,400);
    while(!gameState.getAvailableActions().empty())
    {
        std::cout<< "Main Game State: " << gameState.representation() << std::endl;

        int action = 0;
        if(gameState.lastActivePlayer == 1)
        {
            // Last player was no 1, so it's player 2 turn
            action = uctSort(gameState, 100);
        }
        else
        {
            // Last player was no 2 so it's player 1 turn
            action = uctSort(gameState, 1000);
        }

        std::cout<< "Player: " << 3 - gameState.lastActivePlayer << " takes his best move: " << action << std::endl;
        gameState.performAction(action);
    }

    if(gameState.getValue(gameState.lastActivePlayer) == 1)
    {
        std::cout<< gameState.lastActivePlayer << " wins" << std::endl;
    }
    else
    {
        std::cout<< 3 - gameState.lastActivePlayer << " wins" << std::endl;
    }

    // std::cout<< node3->wins << std::endl;
    //for(std::vector<MctsNode>::iterator it = node.childNodes.begin(); it != node.childNodes.end(); ++it)
    //{
    //    // std::cout<< it->wins  << std::endl;
    //}

    // Finalize the MPI environment.
    //MPI::Finalize();
}
