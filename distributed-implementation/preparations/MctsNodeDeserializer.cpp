//
// Created by agondek on 12/6/15.
//

#include <algorithm>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "MctsNodeDeserializer.h"

unsigned long GetIndexOfFirstNthElementInString(std::string text, char characterToFind, int n)
{
    int timesOFCharacterBeeingFound = 0;
    for(unsigned long i = 0; i < text.length(); i++)
    {
        if(text[i] == characterToFind)
        {
            timesOFCharacterBeeingFound++;
        }

        if(timesOFCharacterBeeingFound >= n)
        {
            return i;
        }
    }

    return 0;
}

unsigned long GetIndexOfLastNthElementInString(std::string text, char characterToFind, int n)
{
    int timesOFCharacterBeeingFound = 0;
    for(unsigned long i = text.length() - 1; i >= 0; i--)
    {
        if(text[i] == characterToFind)
        {
            timesOFCharacterBeeingFound++;
        }

        if(timesOFCharacterBeeingFound >= n)
        {
            return i;
        }
    }

    return 0;
}

MctsNode MctsNodeDeserializer::Deserialize(std::string payload)
{
    //std::cout<< "Starting deserialization" << std::endl;

    // Serialization format:
    // [previousAction;wins;visits;(actionNotTaken,actionNotTaken,...);(childOne, childTwo,...);]
    std::stringstream payloadstream(payload);
    std::string tmp;
    int readInCounter = 0;

    int previousAction = 0;
    int wins = 0;
    int visits = 0;
    std::vector<int> actionsNotTaken;

    //std::cout<< "Deserialization is about to go into first while loop" << std::endl;
    // This will work well only until it will not try to parse info about node children
    while(std::getline(payloadstream, tmp, ';'))
    {
        //std::cout<< "Deserialization first while loop got line: "<< tmp << std::endl;

        readInCounter++;
        if(readInCounter == 1)
        {
            // First in the serialization is previousAction quantity
            // Note that we have to remove opening bracket '[''
            tmp.erase(std::remove(tmp.begin(), tmp.end(), '['), tmp.end());
            previousAction = atoi(tmp.c_str());
            continue;
        }
        else if(readInCounter == 2)
        {
            // Second in the serialization is wins quantity
            wins = atoi(tmp.c_str());
            continue;
        }
        else if(readInCounter == 3)
        {
            // Third in the serialization is visits quantity
            visits = atoi(tmp.c_str());
            continue;
        }
        else if(readInCounter == 4)
        {
            //Fourth in the serialization is actionsNotTaken vector
            // It is serialized as (number,number,...)
            std::string number;
            std::stringstream actionsNotTakenStream(tmp);

            // Reading in series of actions not taken
            while(std::getline(actionsNotTakenStream, number, ','))
            {
                if(number == " ")
                {
                    continue;
                }

                actionsNotTaken.push_back(atoi(number.c_str()));
            }
        }

        // Now there is only information about children nodes left,
        //std::cout<< "Deserialization first while loop breaking: "<< std::endl;
        break;
    }

    //std::cout<< "Deserialization first while loop finished" << std::endl;

    // Clear stream
    payloadstream.str("");
    payloadstream.clear();
    tmp = "";

    //std::cout<< "Deserialization response Node creation started" << std::endl;

    // Crate node
    MctsNode node(previousAction, NULL, NULL);
    node.previousAction = previousAction;
    node.actionsNotTaken = actionsNotTaken;
    node.wins = wins;
    node.visits = visits;

    //std::cout<< "Deserialization response Node creation ended" << std::endl;

    // Now we need to parse information about children
    // It's starts after 4rth semicolon

    //std::cout<< "Deserialization getting index of starting children data" << std::endl;

    unsigned long indexOfChildrenDataBegin = GetIndexOfFirstNthElementInString(payload, ';', 4);

    //std::cout<< "Deserialization index of starting children data: " << indexOfChildrenDataBegin << std::endl;

    if(indexOfChildrenDataBegin > 0)
    {
        //std::cout<< "Deserialization starting processing of children data " << std::endl;

        indexOfChildrenDataBegin++;

        //std::cout<< "Deserialization about to trim payload start" << std::endl;
        //std::cout<< "Deserialization payload before: " << payload << std::endl;

        // Removing start of payload, to retain only children data
        tmp = payload.substr(indexOfChildrenDataBegin, (payload.length() - 1));

        //std::cout<< "Deserialization payload after: " << tmp << std::endl;
        //std::cout<< "Deserialization getting index of ending children data" << std::endl;

        // Children data ends just after first semicolon from the end
        unsigned long indexOfChildrenDataEnd = GetIndexOfLastNthElementInString(tmp, ';', 1);

        //std::cout<< "Deserialization index of ending children data" << indexOfChildrenDataEnd << std::endl;
        //std::cout<< "Deserialization about to trim payload end" << std::endl;
        //std::cout<< "Deserialization payload before: " << tmp << std::endl;

        // Removing end of payload, to retain only children data
        tmp = tmp.substr(0, indexOfChildrenDataEnd);

        //std::cout<< "Deserialization payload after: " << tmp << std::endl;
        //std::cout<< "Deserialization Checking if node has any children" << std::endl;

        // Checking if node has any children
        if(tmp != "()" && tmp != "(|)")
        {
            //std::cout<< "Deserialization node has children!" << std::endl;
            //std::cout<< "Deserialization about to trim children payload | " << std::endl;
            //std::cout<< "Deserialization children payload before: " << tmp << std::endl;

            //Remove starting and ending brackets, and last '|' which are first and 2 last char
            tmp = tmp.substr(1, tmp.length() - 3);

            //std::cout<< "Deserialization children payload after: " << tmp << std::endl;

            // Very awesome node separation logic 100% optimal
            // Wow Cpp such power, easy in use much, wow
            // In short - iterate over whole string, find each [xxx], and add as node
            unsigned long indexOfFirstOpeningBracket = 0;
            unsigned long indexOfLastClosingBracket = 0;
            int numberOfOpeningSquareBracketsFound = 0;
            int numberOfClosingSquareBracketsFound = 0;

            //std::cout<< "Deserialization about to start Such WOW Much loop " << std::endl;

            for(unsigned long i = 0; i < tmp.length() - 1; i++)
            {
                //std::cout<< "Deserialization CHUJ DUPA KURWA CIPA: " << i << "/" << tmp.length()-1 << std::endl;
                //std::cout<< "Deserialization Such WOW Much loop over tmp: " << tmp << std::endl;
                //std::cout<< "Deserialization Such WOW Much loop tmp[i]: " << tmp[i] << std::endl;
                if(tmp[i] == '[')
                {
                    if(numberOfOpeningSquareBracketsFound == 0)
                    {
                        indexOfFirstOpeningBracket = i;
                    }

                    numberOfOpeningSquareBracketsFound++;
                }
                else if(tmp[i] == ']')
                {
                    numberOfClosingSquareBracketsFound++;
                }

                if(numberOfOpeningSquareBracketsFound == numberOfClosingSquareBracketsFound
                        && numberOfOpeningSquareBracketsFound > 0
                        && numberOfClosingSquareBracketsFound > 0)
                {
                    indexOfLastClosingBracket = i;
                    // Create node from data
                    MctsNode child = MctsNodeDeserializer::Deserialize(
                            tmp.substr(indexOfFirstOpeningBracket, indexOfLastClosingBracket));
                    node.childNodes.push_back(child);

                    //Reset all
                    indexOfFirstOpeningBracket = 0;
                    indexOfLastClosingBracket = 0;
                    numberOfOpeningSquareBracketsFound = 0;
                    numberOfClosingSquareBracketsFound = 0;
                }
            }
        }

        //std::cout<< "Deserialization ends Such WOW Much loop " << tmp << std::endl;
    }

    //std::cout<< "Deserialization about to return value" << std::endl;

    return node;
}