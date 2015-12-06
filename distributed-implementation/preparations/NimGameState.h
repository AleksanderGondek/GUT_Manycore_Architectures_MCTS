//
// Created by agondek on 12/6/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_NIMGAMESTATE_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_NIMGAMESTATE_H

#include <iostream>
#include <bits/stl_vector.h>

class NimGameState
{
    public:
        int lastActivePlayer;
        int chips;

        NimGameState(int lastActivePlayer, int chips);

        NimGameState clone(void);
        void performAction(int action);
        std::vector<int> getAvailableActions(void);
        int getValue(int playerId);
        std::string representation(void);
};


#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_NIMGAMESTATE_H
