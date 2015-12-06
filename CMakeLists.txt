cmake_minimum_required(VERSION 3.3)
project(GUT_Manycore_Architectures_MCTS)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        # distributed-implementation/preparations/hello.c
        distributed-implementation/preparations/main.cpp
        distributed-implementation/preparations/NimGameState.cpp
        distributed-implementation/preparations/NimGameState.h
        distributed-implementation/preparations/MctsNode.cpp
        distributed-implementation/preparations/MctsNode.h
        distributed-implementation/preparations/UctSortMcts.cpp
        distributed-implementation/preparations/UtcSortMcts.h
        distributed-implementation/preparations/MctsNodeSerializer.cpp
        distributed-implementation/preparations/MctsNodeSerializer.h
        distributed-implementation/preparations/MctsNodeDeserializer.cpp
        distributed-implementation/preparations/MctsNodeDeserializer.h distributed-implementation/preparations/MctsTreeMerger.cpp distributed-implementation/preparations/MctsTreeMerger.h)

add_executable(GUT_Manycore_Architectures_MCTS ${SOURCE_FILES})
target_link_libraries(GUT_Manycore_Architectures_MCTS ${MPI_LIBRARIES})

if(MPI_COMPILE_FLAGS)
    set_target_properties(GUT_Manycore_Architectures_MCTS PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
    set_target_properties(GUT_Manycore_Architectures_MCTS PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()