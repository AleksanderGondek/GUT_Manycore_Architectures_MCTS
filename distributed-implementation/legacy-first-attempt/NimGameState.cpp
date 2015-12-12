//
// Created by agondek on 12/6/15.
//

#include <sstream>
#include <vector>
#include "NimGameState.h"

NimGameState::NimGameState(int lastActivePlayer, int chips)
{
    this->lastActivePlayer = lastActivePlayer;
    this->chips = chips;
}

NimGameState NimGameState::clone(void)
{
    NimGameState deepClone(this->lastActivePlayer, this->chips);
    return deepClone;
}

void NimGameState::performAction(int action)
{
    this->chips -= action;
    this->lastActivePlayer = 3 - this->lastActivePlayer;
}

std::vector<int> NimGameState::getAvailableActions(void)
{
    std::vector<int> actions;
    if(this->chips > 0)
    {
        for(int i=1; i<std::min(4,(this->chips+1)); i++) //TODO: Why plus 1
        {
            actions.push_back(i);
        }
    }

    return actions;
}

std::string NimGameState::representation(void)
{
    std::stringstream buffer;
    buffer << "Last active player: " << this->lastActivePlayer << "; Chips: " << this->chips << std::endl;
    return buffer.str();
}

int NimGameState::getValue(int playerId)
{
    if(this->lastActivePlayer == playerId)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}