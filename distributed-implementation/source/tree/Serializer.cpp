//
// Created by agondek on 12/12/15.
//

#include "Serializer.h"

namespace Mcts
{
    namespace Tree
    {
        namespace Serialization
        {
            std::string SerializeActionsNotTaken(std::vector<std::string> actionsNotTaken)
            {
                std::stringstream buffer;
                for(std::vector<std::string>::iterator it = actionsNotTaken.begin();
                    it != actionsNotTaken.end(); ++it)
                {
                    buffer << *it << ",";
                }

                return buffer.str();
            }

            std::string Serialize(Mcts::Tree::Node node)
            {
                // Serialization format:
                // [previousAction;wins;visits;(actionNotTaken,actionNotTaken,...);(childOne|childTwo|...);]

                std::stringstream buffer;
                buffer << "["
                << node.getPreviousAction() << ";"
                << node.getWins() << ";"
                << node.getVisits() << ";"
                << "("
                << SerializeActionsNotTaken(node.actionsNotTaken) << ","
                << ")" << ";"

                << "(";
                for(std::vector<Mcts::Tree::Node>::iterator it = node.childNodes.begin();
                    it != node.childNodes.end(); ++it)
                {
                    buffer << Serialize(*it) << "|";
                }
                buffer << ");]";

                return buffer.str();
            }
        }
    }
}