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
        distributed-implementation/preparations/MctsNodeDeserializer.h
        distributed-implementation/preparations/MctsTreeMerger.cpp
        distributed-implementation/preparations/MctsTreeMerger.h)

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
