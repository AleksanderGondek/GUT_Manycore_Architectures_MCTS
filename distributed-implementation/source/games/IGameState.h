//
// Created by agondek on 13/12/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_IGAMESTATE_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_IGAMESTATE_H

#include "../MctsCommon.h"

namespace Mcts
{
    namespace GameStates
    {
        class IGameState
        {
            public:
                IGameState(){}
                virtual ~IGameState(){}

                virtual IGameState* clone(void) = 0;

                virtual unsigned short int getLastActivePlayer(void) = 0;
                virtual void setLastActivePlayer(unsigned short int playerId) = 0;

                virtual long int getStateValue(unsigned short int playerId) = 0;
                virtual std::vector<std::string> getAvailableActions(void) = 0;
                virtual void performAction(std::string action) = 0;
                virtual std::string getGameRepresentation(void) = 0;
        };
    }
}


#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_IGAMESTATE_H
