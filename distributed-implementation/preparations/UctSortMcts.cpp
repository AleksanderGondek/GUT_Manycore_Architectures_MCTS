//
// Created by agondek on 12/6/15.
//
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <mpi.h>
#include "MctsNode.h"
#include "MctsNodeSerializer.h"
#include "MctsNodeDeserializer.h"
#include "MctsTreeMerger.h"
#include "UtcSortMcts.h"

bool compareNodesByVisists(const MctsNode &node1, const MctsNode &node2)
{
    return (node1.visits < node2.visits);
}

int uctSort(NimGameState rootState, int maximumIterations, bool useRanks)
{
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

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


    if(useRanks && world_size > 1)
    {
        // Root synchronization
        std::string serialized = MctsNodeSerializer::Serialize(root);
        serialized += "#";
        if (world_rank == 0)
        {
            //std::cout << "Sending:" << serialized.length() << "/" << DEFAULT_MESSAGE_SIZE << std::endl;
            //std::cout << "Rank 0, root looks before merge: " << serialized << std::endl;
        }

        if (serialized.length() > DEFAULT_MESSAGE_SIZE)
        {
            std::cout << "Error:" << serialized.length() << "/" << DEFAULT_MESSAGE_SIZE << std::endl;
            std::cout << "Seralized tree is too big!" << std::endl;
            return -1;
        }

        if (serialized.length() < DEFAULT_MESSAGE_SIZE)
        {
            serialized.resize(DEFAULT_MESSAGE_SIZE, '@');
        }

        char *rcv_buffer = new char[DEFAULT_MESSAGE_SIZE * world_size];

        MPI_Allgather(serialized.c_str(), DEFAULT_MESSAGE_SIZE, MPI::CHAR,
                      rcv_buffer, DEFAULT_MESSAGE_SIZE, MPI::CHAR,
                      MPI_COMM_WORLD);


        std::string received(rcv_buffer, (unsigned long) (DEFAULT_MESSAGE_SIZE * world_size));
        delete rcv_buffer;

        //long ct = std::count(received.begin(), received.end(), '@');

        received.erase(std::remove(received.begin(), received.end(), '@'), received.end());
        std::stringstream receivedDataStream(received);
        //std::cout << "All data: " << received << std::endl;
        std::string serializedTree;
        while (std::getline(receivedDataStream, serializedTree, '#'))
        {
            serializedTree = serializedTree.substr(0, serializedTree.length() - 1);
            if (world_rank == 0)
            {
                //std::cout << "Rank 0, deserialized new tree before unboxing: " << serializedTree << std::endl;
                //std::cout << serialized.length() << std::endl;
                //std::cout << "There was " << ct << "/" << DEFAULT_MESSAGE_SIZE*world_size << "empty chars in data for iteration " << i << std::endl;
                //std::cout << "Attempting to deserialize data: '" << serializedTree << "'" <<  std::endl;
                //std::cout << "Attempting to deserialize data.. '" <<  std::endl;
                MctsNode remoteTree = MctsNodeDeserializer::Deserialize(serializedTree);


                //std::cout << "Rank 0, root before merge: " << MctsNodeSerializer::Serialize(root) << std::endl;
                //std::cout << "Rank 0, newTree before merge: " << MctsNodeSerializer::Serialize(root) << std::endl;
                //std::cout << "Data deserialized" << std::endl;
                //std::cout << "Attempting to merge" << std::endl;
                MctsTreeMerger::MergeTrees(&root, &remoteTree);

                std::cout << "Rank 0, after merge: " << MctsNodeSerializer::Serialize(root) << std::endl;
                //std::cout << "Merge is done" << std::endl;
            }
            else
            {
                MctsNode remoteTree = MctsNodeDeserializer::Deserialize(serializedTree);
                MctsTreeMerger::MergeTrees(&root, &remoteTree);
            }
        }
    }

    std::sort(root.childNodes.begin(), root.childNodes.end(), compareNodesByVisists);
    MctsNode lastItem = root.childNodes.back();
//    if(world_rank == 0)
//    {
//        //std::cout << MctsNodeSerializer::Serialize(root) << std::endl;
//        for(std::vector<MctsNode>::iterator it = root.childNodes.begin(); it != root.childNodes.end(); ++it)
//        {
//            std::cout << it->representation() << std::endl;
//        }
//    }
    // std::cout<< "RootState @exit: "<< rootState.representation() << std::endl;
    return lastItem.previousAction;
}