#!/bin/bash

# Remove previously build runnable file
rm GUT_Manycore_Architectures_MCTS

# Build
cmake -D CMAKE_C_COMPILER=icc -D CMAKE_CXX_COMPILER=mpiicc ./
make

scp GUT_Manycore_Architectures_MCTS mic0:~
scp GUT_Manycore_Architectures_MCTS mic1:~