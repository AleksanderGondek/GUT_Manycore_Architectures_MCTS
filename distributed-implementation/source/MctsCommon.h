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
#include <sstream>
#include <vector>

// Includes for MPI
#include <mpi.h>

// Constants definitions
#define DEFAULT_MESSAGE_SIZE 65536 // Maximum size of MPI Message to be send - currently 2^16
// TODO: Lower the size

#endif //GUT_MANYCORE_ARCHITECTURES_MCTS_MCTSCOMMONHEADER_H
