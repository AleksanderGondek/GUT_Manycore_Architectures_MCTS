cmake_minimum_required(VERSION 2.8)
project(GUT_Manycore_Architectures_MCTS)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

# Can be DEV or GUT
set(LOCATION DEV)
if(LOCATION STREQUAL DEV)
    # In dev enviorment we don't need no fancy switches, we can safely use c++ 11
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
    # On GUT machine we want to compile to Xeon Phi device, c++0x is best we get
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmic -DMPICH_IGNORE_CXX_SEEK -std=c++0x")
endif()

set(SOURCE_FILES
        distributed-implementation/source/MctsCommon.h
        distributed-implementation/source/games/NimGameState.cpp
        distributed-implementation/source/games/NimGameState.h
        distributed-implementation/source/tree/Node.cpp
        distributed-implementation/source/tree/Node.h
        distributed-implementation/source/tree/Serializer.cpp
        distributed-implementation/source/tree/Serializer.h
        distributed-implementation/source/tree/Deserializer.cpp
        distributed-implementation/source/tree/Deserializer.h
        distributed-implementation/source/tree/Merger.cpp
        distributed-implementation/source/tree/Merger.h
        distributed-implementation/source/playouts/WithUctSort.cpp
        distributed-implementation/source/playouts/WithUctSort.h
        distributed-implementation/source/MctsMain.cpp
        distributed-implementation/source/games/ChessGameState.cpp
        distributed-implementation/source/games/ChessGameState.h
        distributed-implementation/source/parsers/ChessGameParser.cpp
        distributed-implementation/source/parsers/ChessGameParser.h
        distributed-implementation/source/utils/ChessBoardRepresentations.cpp
        distributed-implementation/source/utils/ChessBoardRepresentations.h)

add_executable(GUT_Manycore_Architectures_MCTS ${SOURCE_FILES})
target_link_libraries(GUT_Manycore_Architectures_MCTS ${MPI_LIBRARIES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "distributed-implementation/runnable/")
if(MPI_COMPILE_FLAGS)
    set_target_properties(GUT_Manycore_Architectures_MCTS PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
    set_target_properties(GUT_Manycore_Architectures_MCTS PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()
