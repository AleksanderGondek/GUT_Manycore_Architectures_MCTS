//
// Created by agondek on 09/12/15.
//

#include "NimGameState.h"

namespace Mcts
{
    namespace GameStates
    {
        NimGameState::NimGameState(unsigned short int lastActivePlayer, unsigned int chips)
        {
            this->setLastActivePlayer(lastActivePlayer);
            this->setChips(chips);
        }

        NimGameState NimGameState::clone(void)
        {
            NimGameState deepClone(this->_lastActivePlayer, this->_chips);
            return deepClone;
        }

        void NimGameState::performAction(std::string action)
        {
            unsigned long int quantityOfChipsToRemoveLong = std::stoul(action.c_str(), NULL, 10);
            unsigned int quantityOfChipsToRemove = (unsigned int) quantityOfChipsToRemoveLong;
            if(quantityOfChipsToRemove != quantityOfChipsToRemoveLong)
            {
                std::cout << "Could not properly convert string to usigned int" << std::endl;
            }

            if(quantityOfChipsToRemove > this->getChips())
            {
                this->setChips(0);
            }
            else
            {
                this->setChips(this->getChips() - quantityOfChipsToRemove);
            }

            this->setLastActivePlayer((unsigned short int)(3 - this->getLastActivePlayer()));
        }

        std::vector<std::string> NimGameState::getAvailableActions(void)
        {
            std::vector<std::string> actions;
            if(this->_chips > 0)
            {
                for(int i=1; i<std::min((unsigned int)4,(this->_chips + 1)); i++)
                {
                    // c++0x in action - std:to_string
                    actions.push_back(std::to_string(i));
                }
            }

            return actions;
        }

        unsigned long int NimGameState::getStateValue(unsigned short int playerId)
        {
            return this->_lastActivePlayer == playerId ? 1 : 0;
        }

        // Getters and setters
        unsigned int NimGameState::getChips(void)
        {
            return this->_chips;
        }

        void NimGameState::setChips(unsigned int number)
        {
            this->_chips = number;
        }

        unsigned short int NimGameState::getLastActivePlayer(void)
        {
            return this->_lastActivePlayer;
        }

        void NimGameState::setLastActivePlayer(unsigned short int playerId)
        {
            this->_lastActivePlayer = playerId;
        }
    }
}