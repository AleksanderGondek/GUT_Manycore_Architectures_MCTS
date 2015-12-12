//
// Created by agondek on 09/12/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_NIMGAMESTATE_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_NIMGAMESTATE_H

#include "../MctsCommon.h"

namespace Mcts
{
    namespace GameStates
    {
        class NimGameState
        {
            public:
                NimGameState(unsigned short int lastActivePlayer, unsigned int chips);
                NimGameState clone(void);

                unsigned int getChips(void);
                void setChips(unsigned int number);

                unsigned short int getLastActivePlayer(void);
                void setLastActivePlayer(unsigned short int playerId);

                unsigned long int getStateValue(unsigned short int playerId);
                std::vector<std::string> getAvailableActions(void);
                void performAction(std::string action);

            private:
                unsigned int _chips;
                unsigned short int _lastActivePlayer;
        };
    }
}

#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_NIMGAMESTATE_H
