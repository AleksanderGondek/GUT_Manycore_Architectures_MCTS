//
// Created by agondek on 12/6/15.
//

#include <sstream>
#include <vector>
#include "MctsNodeSerializer.h"

std::string SerializeActionsNotTaken(std::vector<int> actionsNotTaken)
{
    std::stringstream buffer;
    for(std::vector<int>::iterator it = actionsNotTaken.begin(); it != actionsNotTaken.end(); ++it)
    {
        buffer << *it << ",";
    }

    return buffer.str();
}

std::string MctsNodeSerializer::Serialize(MctsNode node)
{
    // Serialization format:
    // [previousAction;wins;visits;(actionNotTaken,actionNotTaken,...);(childOne|childTwo|...);]

    std::stringstream buffer;
    buffer << "["
            << node.previousAction << ";"
            << node.wins << ";"
            << node.visits << ";"
            << "("
                << SerializeActionsNotTaken(node.actionsNotTaken) << ","
            << ")" << ";"
            << "(";
            for(std::vector<MctsNode>::iterator it = node.childNodes.begin(); it != node.childNodes.end(); ++it)
            {
                buffer << Serialize(*it) << "|";
            }
    buffer << ");]";
    return buffer.str();
}