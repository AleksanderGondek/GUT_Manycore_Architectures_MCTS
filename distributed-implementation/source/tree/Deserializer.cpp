//
// Created by agondek on 12/12/15.
//

#include "Deserializer.h"

namespace Mcts
{
    namespace Tree {
        namespace Deserialization {
            unsigned long GetIndexOfFirstNthElementInString(std::string text, char characterToFind, int n) {
                int timesOFCharacterBeingFound = 0;
                for (unsigned long i = 0; i < text.length(); i++) {
                    if (text[i] == characterToFind) {
                        timesOFCharacterBeingFound++;
                    }

                    if (timesOFCharacterBeingFound >= n) {
                        return i;
                    }
                }

                return 0;
            }

            unsigned long GetIndexOfLastNthElementInString(std::string text, char characterToFind, int n) {
                int timesOFCharacterBeingFound = 0;
                for (unsigned long i = text.length() - 1; i >= 0; i--) {
                    if (text[i] == characterToFind) {
                        timesOFCharacterBeingFound++;
                    }

                    if (timesOFCharacterBeingFound >= n) {
                        return i;
                    }
                }

                return 0;
            }

            Mcts::Tree::Node Deserialize(std::string payload)
            {
                // Serialization format:
                // [previousAction;wins;visits;(actionNotTaken,actionNotTaken,...);(childOne, childTwo,...);]

                std::stringstream payloadStream(payload);
                std::string tmp;

                int readInCounter = 0;
                std::string previousAction = MCTS_ACTION_NOT_AVAILABLE;
                long int wins = 0;
                unsigned long int visits = 0;
                std::vector<std::string> actionsNotTaken;

                // This loop is supposed to handle all node data except for child nodes
                while (std::getline(payloadStream, tmp, ';')) {
                    readInCounter++;
                    if (readInCounter == 1) {
                        // First in the serialization is previousAction
                        // Note that we have to remove opening bracket '[''
                        tmp.erase(std::remove(tmp.begin(), tmp.end(), '['), tmp.end());

                        // previousAction = atoi(tmp.c_str());
                        // TODO: Make sure this works as expects
                        previousAction = tmp;

                        continue;
                    }
                    else if (readInCounter == 2) {
                        // Second in the serialization is wins quantity

                        // wins = atoi(tmp.c_str());
                        // TODO: Make sure this works as expects
                        // We are using stroul to enable unsigned long number
                        wins = strtoul(tmp.c_str(), NULL, 10);
                        continue;
                    }
                    else if (readInCounter == 3) {
                        // Third in the serialization is visits quantity

                        // visits = atoi(tmp.c_str());
                        // TODO: Make sure this works as expects
                        // We are using stroul to enable unsigned long number
                        visits = strtoul(tmp.c_str(), NULL, 10);
                        continue;
                    }
                    else if (readInCounter == 4) {
                        //Fourth in the serialization is actionsNotTaken vector
                        // It is serialized as (number,number,...)

                        //Remove starting and ending brackets
                        tmp = tmp.substr(1, tmp.length() - 2);

                        std::string number;
                        std::stringstream actionsNotTakenStream(tmp);

                        // Reading in series of actions not taken
                        while (std::getline(actionsNotTakenStream, number, ',')) {
                            if (number == " ") {
                                continue;
                            }

                            int atoiNumber = atoi(number.c_str());
                            // Dirty hack for Cpp retardness
                            // TODO 2: Later we need to change it to accept encoded actions as 3AAC
                            if (atoiNumber > 0) {
                                actionsNotTaken.push_back(std::to_string(atoiNumber));
                            }
                        }
                    }

                    // Now there is only information about children nodes left,
                    break;
                }

                // Clear stream
                payloadStream.str("");
                payloadStream.clear();
                tmp = "";

                // Crate deserialized node
                Mcts::Tree::Node node(previousAction, NULL, NULL);
                node.actionsNotTaken = actionsNotTaken;
                node.adjustWins(wins);
                node.adjustVisits(visits);

                // Now we need to parse information about children
                // It's starts after 4rth semicolon
                unsigned long indexOfChildrenDataBegin = GetIndexOfFirstNthElementInString(payload, ';', 4);
                if (indexOfChildrenDataBegin > 0)
                {
                    indexOfChildrenDataBegin++;

                    // Removing start of payload, to retain only children data
                    tmp = payload.substr(indexOfChildrenDataBegin, (payload.length() - 1));

                    // Children data ends just after first semicolon from the end
                    unsigned long indexOfChildrenDataEnd = GetIndexOfLastNthElementInString(tmp, ';', 1);

                    // Removing end of payload, to retain only children data
                    tmp = tmp.substr(0, indexOfChildrenDataEnd);

                    // Checking if node has any children
                    if (tmp != "()" && tmp != "(|)")
                    {
                        //Remove starting and ending brackets, and last '|' which are first and 2 last char
                        tmp = tmp.substr(1, tmp.length() - 3);

                        // Very awesome node separation logic 100% optimal
                        // Wow Cpp such power, easy in use much, wow
                        // In short - iterate over whole string, find
                        // each >>[xxx]<< entry, and add as node
                        unsigned long indexOfFirstOpeningBracket = 0;
                        unsigned long indexOfLastClosingBracket = 0;
                        int numberOfOpeningSquareBracketsFound = 0;
                        int numberOfClosingSquareBracketsFound = 0;
                        for (unsigned long i = 0; i < tmp.length(); i++)
                        {
                            if (tmp[i] == '[')
                            {
                                if (numberOfOpeningSquareBracketsFound == 0)
                                {
                                    indexOfFirstOpeningBracket = i;
                                }

                                numberOfOpeningSquareBracketsFound++;
                            }
                            else if (tmp[i] == ']')
                            {
                                numberOfClosingSquareBracketsFound++;
                            }

                            if (numberOfOpeningSquareBracketsFound == numberOfClosingSquareBracketsFound
                                && numberOfOpeningSquareBracketsFound > 0
                                && numberOfClosingSquareBracketsFound > 0)
                            {
                                indexOfLastClosingBracket = i;

                                // This is why we can't have nice things
                                // Glorious and comfy cpp
                                // ( I am rambling because I have spent 1h+ wondering why
                                // it won't work without that indexOfLastClosingBracket +1 )
                                std::string preview = tmp.substr(indexOfFirstOpeningBracket,
                                                                 (indexOfLastClosingBracket + 1) -
                                                                 indexOfFirstOpeningBracket);

                                // Create node from data
                                Mcts::Tree::Node child = Deserialize(preview);

                                //Add new node to child nodes
                                node.childNodes.push_back(child);

                                // Reset all variables responsible for
                                // finding child nodes
                                indexOfFirstOpeningBracket = 0;
                                indexOfLastClosingBracket = 0;
                                numberOfOpeningSquareBracketsFound = 0;
                                numberOfClosingSquareBracketsFound = 0;
                            }
                        }
                    }
                }

                return node;
            }
        }
    }
};