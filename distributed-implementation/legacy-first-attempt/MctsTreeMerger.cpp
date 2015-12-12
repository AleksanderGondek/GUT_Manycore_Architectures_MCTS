//
// Created by agondek on 12/6/15.
//
#include <algorithm>
#include <vector>
#include "MctsTreeMerger.h"

//tmp
#include <mpi.h>


void BalanceNodes(MctsNode* local, MctsNode* remote)
{
    //std::cout << "Balacing the following nodes" << std::endl;
    //std::cout << "Local node: " << local->representation() << std::endl;
    //std::cout << "Remote node: " << remote->representation() << std::endl;

    //std::cout << "Balacing wins" << std::endl;

//    int winsDelta = local->wins - remote->wins;
//    if(winsDelta > 0)
//    {
//        // If remote has less wins in this node, adjust this nodes wins down
//        local->wins -= winsDelta;
//    }
//    else if (winsDelta < 0)
//    {
//        // IF remote has more wins in this node, adjust this node wins up
//        local->wins += winsDelta;
//    }
//
//
//    int visitsDelta = local->visits - remote->visits;
//    if(visitsDelta > 0)
//    {
//        // If remote has less wins in this node, adjust this nodes wins down
//        local->visits -= visitsDelta;
//    }
//    else if (visitsDelta < 0)
//    {
//        // IF remote has more wins in this node, adjust this node wins up
//        local->visits += visitsDelta;
//    }

    local->wins += remote->wins;
    //std::cout << "Balacing visits" << std::endl;
    local->visits += remote->visits;

    // Get the rank of the process
//    int world_rank;
//    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
//    if((local->wins  < 0 || local->visits < 0) && world_rank == 0)
//    {
//        std::cout << "ERROR BALANCING NODES" << std::endl;
//        std::cout << "Local node: " << local->representation() << std::endl;
//        std::cout << "Remote node: " << remote->representation() << std::endl;
//    }

    //std::cout << "Balancing actions not taken" << std::endl;
    // Compare actions not taken
    // If remote has no actions taken and locally we have some left
    if(remote->actionsNotTaken.size() == 0 && local->actionsNotTaken.size() > 0)
    {
        local->actionsNotTaken.clear();
    }
    // If remote has some actions taken and we have none left
    else if(remote->actionsNotTaken.size() > 0 && local->actionsNotTaken.size() == 0)
    {
        ;
        // NOOP
    }
    // If remote and local differs but none are empty
    else if (remote->actionsNotTaken.size() > 0 && local->actionsNotTaken.size() > 0 &&
            remote->actionsNotTaken.size() != local->actionsNotTaken.size())
    {
        //std::cout << "Started comparistion of actions not taken" << std::endl;
        // We should ignore actions that we don't have but remote has
        // But we should remove actions that remote has not and we do
        std::vector<int>::iterator it = local->actionsNotTaken.begin();
        std::vector<int> toBeRemoved;
        while(it != local->actionsNotTaken.end())
        {
            ////std::cout << "Checking remote: " << *it << std::endl;
            if(std::find(remote->actionsNotTaken.begin(), remote->actionsNotTaken.end(), *it) == remote->actionsNotTaken.end())
            {
                if(*it == 0)
                {
                    continue;
                }

                toBeRemoved.push_back(*it);
            }
            ++it;
        }

        for(std::vector<int>::iterator removeIt = toBeRemoved.begin(); removeIt != toBeRemoved.end(); ++removeIt)
        {
            local->actionsNotTaken.erase(std::remove(
                                                 local->actionsNotTaken.begin(),
                                                 local->actionsNotTaken.end(),
                                                 *removeIt),
                                         local->actionsNotTaken.end());
        }
    }


    //std::cout << "Balacing children nodes" << std::endl;
    // Merge all remote children
    std::vector<MctsNode>::iterator it = remote->childNodes.begin();
    while(it != remote->childNodes.end())
    {
        // Find same node in the local children
        MctsNode* foundElement = NULL;
        for(std::vector<MctsNode>::iterator localIt = local->childNodes.begin(); localIt != local->childNodes.end(); ++localIt)
        {
            if(localIt->previousAction == it->previousAction)
            {
                foundElement = &(*localIt);
                break;
            }
        }

        // If child was found
        if(foundElement != NULL)
        {
            BalanceNodes(foundElement, &(*it));
        }
        //Child was not found
        else
        {
            MctsNode remoteNewNode = *it;
            MctsNode newNode(remoteNewNode.previousAction, local, NULL);
            MctsNode* newNodePtr = &newNode;
            newNode.lastActivePlayer = 0;
            newNode.actionsNotTaken = remoteNewNode.actionsNotTaken;

            // Remove action from possible actions
            local->actionsNotTaken.erase(std::remove(local->actionsNotTaken.begin(),
                                                     local->actionsNotTaken.end(),
                                                     remoteNewNode.previousAction),
                                         local->actionsNotTaken.end());
            // Add node
            local->childNodes.push_back(newNode);

            // Recursive
            BalanceNodes(newNodePtr, &remoteNewNode);
        }

        ++it;
    }
}

void MctsTreeMerger::MergeTrees(MctsNode *local, MctsNode *remote)
{
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if((local->wins  < 0 || local->visits < 0 || remote->wins < 0 || remote->visits <0 ) && world_rank == 0)
    {
        std::cout << "ERROR BALANCING NODES" << std::endl;
        std::cout << "Local node: " << local->representation() << std::endl;
        std::cout << "Remote node: " << remote->representation() << std::endl;
    }

    MctsNode* localRoot = local;
    MctsNode* remoteRoot = remote;
    BalanceNodes(localRoot, remoteRoot);
}
