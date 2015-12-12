//
// Created by agondek on 12/12/15.
//

#include "Merger.h"

namespace Mcts
{
    namespace Tree
    {
        namespace Merger
        {
            void IncorporateRemoteNodeToLocal(Mcts::Tree::Node* local, Mcts::Tree::Node* remote)
            {
                local->adjustWins(remote->getWins());
                local->adjustVisits(remote->getVisits());

                // Compare actions not taken
                // If remote has no actions taken and locally we have some left
                if(remote->actionsNotTaken.size() == 0 && local->actionsNotTaken.size() > 0)
                {
                    local->actionsNotTaken.clear();
                }
                    // If remote has some actions taken and we have none left
                else if(remote->actionsNotTaken.size() > 0 && local->actionsNotTaken.size() == 0)
                {
                    ; // Do nothing, it is here only for explicit statement that we are skipping
                    // This case
                }
                    // If remote and local differs but none are empty
                else if (remote->actionsNotTaken.size() > 0 && local->actionsNotTaken.size() > 0 &&
                         remote->actionsNotTaken.size() != local->actionsNotTaken.size())
                {
                    // We should ignore actions that we don't have but remote has
                    // But we should remove actions that remote has not and we do
                    // TODO: Can it be done more efficiently
                    std::vector<std::string>::iterator it = local->actionsNotTaken.begin();
                    std::vector<std::string> toBeRemoved;
                    while(it != local->actionsNotTaken.end())
                    {
                        if(std::find(remote->actionsNotTaken.begin(),
                                     remote->actionsNotTaken.end(),
                                     *it) == remote->actionsNotTaken.end())
                        {
                            toBeRemoved.push_back(*it);
                        }

                        ++it;
                    }

                    for(std::vector<std::string>::iterator removeIt = toBeRemoved.begin();
                        removeIt != toBeRemoved.end(); ++removeIt)
                    {
                        local->actionsNotTaken.erase(std::remove(
                                                             local->actionsNotTaken.begin(),
                                                             local->actionsNotTaken.end(),
                                                             *removeIt),
                                                     local->actionsNotTaken.end());
                    }
                }

                // Merge all remote children
                std::vector<Mcts::Tree::Node>::iterator it = remote->childNodes.begin();
                while(it != remote->childNodes.end())
                {
                    // Find same node in the local children
                    Mcts::Tree::Node* foundElement = NULL;
                    for(std::vector<Mcts::Tree::Node>::iterator localIt
                            = local->childNodes.begin();
                        localIt != local->childNodes.end(); ++localIt)
                    {
                        if(localIt->getPreviousAction() == it->getPreviousAction())
                        {
                            foundElement = &(*localIt);
                            break;
                        }
                    }

                    // If child was found
                    if(foundElement != NULL)
                    {
                        IncorporateRemoteNodeToLocal(foundElement, &(*it));
                    }
                        // Child was not found
                    else
                    {
                        Mcts::Tree::Node remoteNewNode = *it;
                        Mcts::Tree::Node newNode(remoteNewNode.getPreviousAction(), local, NULL);
                        newNode.actionsNotTaken = remoteNewNode.actionsNotTaken;

                        // Remove action that created newNode from list of possible actions
                        // of parent node.
                        local->actionsNotTaken.erase(std::remove(local->actionsNotTaken.begin(),
                                                                 local->actionsNotTaken.end(),
                                                                 remoteNewNode.getPreviousAction()),
                                                     local->actionsNotTaken.end());
                        // Add newNode to parent
                        local->childNodes.push_back(newNode);

                        // Recursively incorporate remote children of newNode
                        IncorporateRemoteNodeToLocal(&newNode, &remoteNewNode);
                    }

                    ++it;
                }
            }
        };
    }
}
