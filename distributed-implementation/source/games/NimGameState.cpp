//
// Created by agondek on 09/12/15.
//

#include "NimGameState.h"

namespace Mcts
{
    namespace GameStates
    {
        NimGameState::NimGameState(int lastActivePlayer, int chips)
        {
            this->setLastActivePlayer(lastActivePlayer);
            this->setChips(chips);
        }

        NimGameState NimGameState::clone(void)
        {
            NimGameState deepClone(this->lastActivePlayer, this->chips);
            return deepClone;
        }

        void NimGameState::performAction(std::string action)
        {
            int quantityOfChipsToRemove = atoi(action.c_str());
            this->setChips(this->getChips()- quantityOfChipsToRemove);
            this->setLastActivePlayer(3 - this->getLastActivePlayer());
        }

        std::vector<std::string> NimGameState::getAvailableActions(void)
        {
            std::vector<std::string> actions;
            if(this->chips > 0)
            {
                for(int i=1; i<std::min(4,(this->chips+1)); i++)
                {
                    // c++0x in action - std:to_string
                    actions.push_back(std::to_string(i));
                }
            }

            return actions;
        }

        float NimGameState::getStateValue(int playerId)
        {
            return this->lastActivePlayer == playerId ? 1.0f : 0.0f;
        }

        int NimGameState::getChips(void)
        {
            return this->chips;
        }

        void NimGameState::setChips(int number)
        {
            this->chips = number;
        }

        int NimGameState::getLastActivePlayer(void)
        {
            return this->lastActivePlayer;
        }

        void NimGameState::setLastActivePlayer(int playerId)
        {
            this->lastActivePlayer = playerId;
        }
    }
}