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
                NimGameState(int lastActivePlayer, int chips);
                NimGameState clone(void);

                int getChips(void);
                void setChips(int number);

                int getLastActivePlayer(void);
                void setLastActivePlayer(int playerId);

                float getStateValue(int playerId);
                void performAction(std::string action);
                std::vector<std::string> getAvailableActions(void);

            private:
                int chips;
                int lastActivePlayer;
        };
    }
}

#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_NIMGAMESTATE_H
