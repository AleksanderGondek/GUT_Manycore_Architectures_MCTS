//
// Created by agondek on 12/12/15.
//

#include "WithUctSort.h"

namespace Mcts
{
    namespace Tree
    {
        namespace Playouts
        {
            std::string getBestMoveUsingUtcSort(Mcts::GameStates::NimGameState rootState,
                                                int maximumIterations)
            {
                // Get the id of current process
                int world_rank;
                MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

                // Get the number of processes
                int world_size;
                MPI_Comm_size(MPI_COMM_WORLD, &world_size);

                Mcts::Tree::Node root(0, NULL, &rootState);
                for(int i=0; i<maximumIterations; i++)
                {
                    Mcts::Tree::Node* node = &root;
                    Mcts::GameStates::NimGameState state = rootState.clone();

                    // Selection Step
                    while(node->actionsNotTaken.empty() && !node->childNodes.empty())
                    {
                        node = node->selectNextChildNode();
                        state.performAction(node->getPreviousAction());
                    }

                    // Expansion Step
                    if(!node->actionsNotTaken.empty())
                    {
                        std::random_shuffle(node->actionsNotTaken.begin(), node->actionsNotTaken.end());
                        std::string action = node->actionsNotTaken.back();
                        state.performAction(action);
                        node = node->addChildNode(action, &state);
                    }

                    // Simulation Step
                    while(!state.getAvailableActions().empty())
                    {
                        std::random_shuffle(node->actionsNotTaken.begin(), node->actionsNotTaken.end());
                        std::string action = node->actionsNotTaken.back();
                        state.performAction(action);
                    }

                    // Backpropagation Step
                    while(node->getParentNode() != NULL)
                    {
                        node->update(state.getStateValue(node->getLastActivePlayer()));
                        node = node->getParentNode();
                    }
                }


                // Root synchronization
                std::string serialized = Mcts::Tree::Serialization::Serialize(root);
                serialized += "#";

                if (serialized.length() > MCTS_DEFAULT_MESSAGE_SIZE)
                {
                    std::cout << "Error:" << serialized.length() << "/" << MCTS_DEFAULT_MESSAGE_SIZE << std::endl;
                    std::cout << "Seralized tree is too big!" << std::endl;
                    return MCTS_ACTION_NOT_AVAILABLE;
                }

                if (serialized.length() < MCTS_DEFAULT_MESSAGE_SIZE)
                {
                    serialized.resize(MCTS_DEFAULT_MESSAGE_SIZE, '@');
                }

                char *rcv_buffer = new char[MCTS_DEFAULT_MESSAGE_SIZE * world_size];
                MPI_Allgather((void*)serialized.c_str(), MCTS_DEFAULT_MESSAGE_SIZE, MPI::CHAR,
                              rcv_buffer, MCTS_DEFAULT_MESSAGE_SIZE, MPI::CHAR,
                              MPI_COMM_WORLD);


                std::string received(rcv_buffer, (unsigned long)(MCTS_DEFAULT_MESSAGE_SIZE * world_size));
                delete rcv_buffer;

                received.erase(std::remove(received.begin(), received.end(), '@'), received.end());
                std::stringstream receivedDataStream(received);

                // Load in other MCS Trees
                std::string serializedTree;
                while (std::getline(receivedDataStream, serializedTree, '#'))
                {
                    serializedTree = serializedTree.substr(0, serializedTree.length() - 1);
                    Mcts::Tree::Node remoteTree = Mcts::Tree::Deserializer::Deserialize(serializedTree);
                    Mcts::Tree::Merger::IncorporateRemoteNodeToLocal(&root, &remoteTree);
                }

                std::sort(root.childNodes.begin(), root.childNodes.end(), compareNodesByVisists);
                Mcts::Tree::Node lastItemWithHighestVisits = root.childNodes.back();
                return lastItemWithHighestVisits.getPreviousAction();
            }
        }
    }
}