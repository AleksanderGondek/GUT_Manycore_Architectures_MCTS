//
// Created by agondek on 09/12/15.
//

#ifndef GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSCOMMONHEADER_H
#define GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSCOMMONHEADER_H

// Includes from standard libraries
#include <algorithm>
#include <bits/stl_vector.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <unordered_map>
#include <vector>

// Includes for MPI
#include <mpi.h>

// Constants definitions
#define MCTS_PLAYER_ONE_ID 1
#define MCTS_PLAYER_TWO_ID 2
#define MCTS_PLAYER_UNKNOWN_ID 3

#define MCTS_ACTION_NOT_AVAILABLE "N/A"

#define MCTS_DEFAULT_DECISION_TIMEOUT_MULTIPLAYER 4096
// Maximum 'ticks' that can be spend on decition in MCTS are
// counted as (number of iterations) x (MCTS_DEFAULT_DECISION_TIMEOUT_MULTIPLAYER)
#define MCTS_DEFAULT_MESSAGE_SIZE 65536
// Maximum size of MPI Message to be send - currently 2^16
// TODO: Lower the size

#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSCOMMONHEADER_H
