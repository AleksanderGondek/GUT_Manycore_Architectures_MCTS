//
// Created by agondek on 12/6/15.
//
#include <algorithm>
#include "MctsTreeMerger.h"


void BalanceNodes(MctsNode* local, MctsNode* remote)
{
    if(local->wins != remote->wins)
    {
        int delta = remote->wins - local->wins;
        local->wins += delta;
    }

    if(local->visits != remote->visits)
    {
        int delta = remote->visits - local->visits;
        if(delta > 0) {
            local->visits += delta;
        }
    }

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
        // We should ignore actions that we don't have but remote has
        // But we should remove actions that remote has not and we do
        std::vector<int>::iterator it = local->actionsNotTaken.begin();
        while(it != local->actionsNotTaken.end())
        {
            if(std::find(remote->actionsNotTaken.begin(), remote->actionsNotTaken.end(), *it) == remote->actionsNotTaken.end())
            {
                // If element in local vector was not found in remote
                it = local->actionsNotTaken.erase(it);
            }

            ++it;
        }
    }


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
            BalanceNodes(&(*it), foundElement);
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
    MctsNode* localRoot = local;
    MctsNode* remoteRoot = remote;

    BalanceNodes(localRoot, remoteRoot);
}