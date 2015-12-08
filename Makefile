# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/student01/131508/GUT_Manycore_Architectures_MCTS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/student01/131508/GUT_Manycore_Architectures_MCTS

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/student01/131508/GUT_Manycore_Architectures_MCTS/CMakeFiles /home/student01/131508/GUT_Manycore_Architectures_MCTS/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/student01/131508/GUT_Manycore_Architectures_MCTS/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named GUT_Manycore_Architectures_MCTS

# Build rule for target.
GUT_Manycore_Architectures_MCTS: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 GUT_Manycore_Architectures_MCTS
.PHONY : GUT_Manycore_Architectures_MCTS

# fast build rule for target.
GUT_Manycore_Architectures_MCTS/fast:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build
.PHONY : GUT_Manycore_Architectures_MCTS/fast

distributed-implementation/preparations/MctsNode.o: distributed-implementation/preparations/MctsNode.cpp.o
.PHONY : distributed-implementation/preparations/MctsNode.o

# target to build an object file
distributed-implementation/preparations/MctsNode.cpp.o:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/MctsNode.cpp.o
.PHONY : distributed-implementation/preparations/MctsNode.cpp.o

distributed-implementation/preparations/MctsNode.i: distributed-implementation/preparations/MctsNode.cpp.i
.PHONY : distributed-implementation/preparations/MctsNode.i

# target to preprocess a source file
distributed-implementation/preparations/MctsNode.cpp.i:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/MctsNode.cpp.i
.PHONY : distributed-implementation/preparations/MctsNode.cpp.i

distributed-implementation/preparations/MctsNode.s: distributed-implementation/preparations/MctsNode.cpp.s
.PHONY : distributed-implementation/preparations/MctsNode.s

# target to generate assembly for a file
distributed-implementation/preparations/MctsNode.cpp.s:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/MctsNode.cpp.s
.PHONY : distributed-implementation/preparations/MctsNode.cpp.s

distributed-implementation/preparations/MctsNodeDeserializer.o: distributed-implementation/preparations/MctsNodeDeserializer.cpp.o
.PHONY : distributed-implementation/preparations/MctsNodeDeserializer.o

# target to build an object file
distributed-implementation/preparations/MctsNodeDeserializer.cpp.o:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/MctsNodeDeserializer.cpp.o
.PHONY : distributed-implementation/preparations/MctsNodeDeserializer.cpp.o

distributed-implementation/preparations/MctsNodeDeserializer.i: distributed-implementation/preparations/MctsNodeDeserializer.cpp.i
.PHONY : distributed-implementation/preparations/MctsNodeDeserializer.i

# target to preprocess a source file
distributed-implementation/preparations/MctsNodeDeserializer.cpp.i:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/MctsNodeDeserializer.cpp.i
.PHONY : distributed-implementation/preparations/MctsNodeDeserializer.cpp.i

distributed-implementation/preparations/MctsNodeDeserializer.s: distributed-implementation/preparations/MctsNodeDeserializer.cpp.s
.PHONY : distributed-implementation/preparations/MctsNodeDeserializer.s

# target to generate assembly for a file
distributed-implementation/preparations/MctsNodeDeserializer.cpp.s:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/MctsNodeDeserializer.cpp.s
.PHONY : distributed-implementation/preparations/MctsNodeDeserializer.cpp.s

distributed-implementation/preparations/MctsNodeSerializer.o: distributed-implementation/preparations/MctsNodeSerializer.cpp.o
.PHONY : distributed-implementation/preparations/MctsNodeSerializer.o

# target to build an object file
distributed-implementation/preparations/MctsNodeSerializer.cpp.o:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/MctsNodeSerializer.cpp.o
.PHONY : distributed-implementation/preparations/MctsNodeSerializer.cpp.o

distributed-implementation/preparations/MctsNodeSerializer.i: distributed-implementation/preparations/MctsNodeSerializer.cpp.i
.PHONY : distributed-implementation/preparations/MctsNodeSerializer.i

# target to preprocess a source file
distributed-implementation/preparations/MctsNodeSerializer.cpp.i:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/MctsNodeSerializer.cpp.i
.PHONY : distributed-implementation/preparations/MctsNodeSerializer.cpp.i

distributed-implementation/preparations/MctsNodeSerializer.s: distributed-implementation/preparations/MctsNodeSerializer.cpp.s
.PHONY : distributed-implementation/preparations/MctsNodeSerializer.s

# target to generate assembly for a file
distributed-implementation/preparations/MctsNodeSerializer.cpp.s:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/MctsNodeSerializer.cpp.s
.PHONY : distributed-implementation/preparations/MctsNodeSerializer.cpp.s

distributed-implementation/preparations/MctsTreeMerger.o: distributed-implementation/preparations/MctsTreeMerger.cpp.o
.PHONY : distributed-implementation/preparations/MctsTreeMerger.o

# target to build an object file
distributed-implementation/preparations/MctsTreeMerger.cpp.o:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/MctsTreeMerger.cpp.o
.PHONY : distributed-implementation/preparations/MctsTreeMerger.cpp.o

distributed-implementation/preparations/MctsTreeMerger.i: distributed-implementation/preparations/MctsTreeMerger.cpp.i
.PHONY : distributed-implementation/preparations/MctsTreeMerger.i

# target to preprocess a source file
distributed-implementation/preparations/MctsTreeMerger.cpp.i:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/MctsTreeMerger.cpp.i
.PHONY : distributed-implementation/preparations/MctsTreeMerger.cpp.i

distributed-implementation/preparations/MctsTreeMerger.s: distributed-implementation/preparations/MctsTreeMerger.cpp.s
.PHONY : distributed-implementation/preparations/MctsTreeMerger.s

# target to generate assembly for a file
distributed-implementation/preparations/MctsTreeMerger.cpp.s:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/MctsTreeMerger.cpp.s
.PHONY : distributed-implementation/preparations/MctsTreeMerger.cpp.s

distributed-implementation/preparations/NimGameState.o: distributed-implementation/preparations/NimGameState.cpp.o
.PHONY : distributed-implementation/preparations/NimGameState.o

# target to build an object file
distributed-implementation/preparations/NimGameState.cpp.o:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/NimGameState.cpp.o
.PHONY : distributed-implementation/preparations/NimGameState.cpp.o

distributed-implementation/preparations/NimGameState.i: distributed-implementation/preparations/NimGameState.cpp.i
.PHONY : distributed-implementation/preparations/NimGameState.i

# target to preprocess a source file
distributed-implementation/preparations/NimGameState.cpp.i:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/NimGameState.cpp.i
.PHONY : distributed-implementation/preparations/NimGameState.cpp.i

distributed-implementation/preparations/NimGameState.s: distributed-implementation/preparations/NimGameState.cpp.s
.PHONY : distributed-implementation/preparations/NimGameState.s

# target to generate assembly for a file
distributed-implementation/preparations/NimGameState.cpp.s:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/NimGameState.cpp.s
.PHONY : distributed-implementation/preparations/NimGameState.cpp.s

distributed-implementation/preparations/UctSortMcts.o: distributed-implementation/preparations/UctSortMcts.cpp.o
.PHONY : distributed-implementation/preparations/UctSortMcts.o

# target to build an object file
distributed-implementation/preparations/UctSortMcts.cpp.o:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/UctSortMcts.cpp.o
.PHONY : distributed-implementation/preparations/UctSortMcts.cpp.o

distributed-implementation/preparations/UctSortMcts.i: distributed-implementation/preparations/UctSortMcts.cpp.i
.PHONY : distributed-implementation/preparations/UctSortMcts.i

# target to preprocess a source file
distributed-implementation/preparations/UctSortMcts.cpp.i:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/UctSortMcts.cpp.i
.PHONY : distributed-implementation/preparations/UctSortMcts.cpp.i

distributed-implementation/preparations/UctSortMcts.s: distributed-implementation/preparations/UctSortMcts.cpp.s
.PHONY : distributed-implementation/preparations/UctSortMcts.s

# target to generate assembly for a file
distributed-implementation/preparations/UctSortMcts.cpp.s:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/UctSortMcts.cpp.s
.PHONY : distributed-implementation/preparations/UctSortMcts.cpp.s

distributed-implementation/preparations/main.o: distributed-implementation/preparations/main.cpp.o
.PHONY : distributed-implementation/preparations/main.o

# target to build an object file
distributed-implementation/preparations/main.cpp.o:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/main.cpp.o
.PHONY : distributed-implementation/preparations/main.cpp.o

distributed-implementation/preparations/main.i: distributed-implementation/preparations/main.cpp.i
.PHONY : distributed-implementation/preparations/main.i

# target to preprocess a source file
distributed-implementation/preparations/main.cpp.i:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/main.cpp.i
.PHONY : distributed-implementation/preparations/main.cpp.i

distributed-implementation/preparations/main.s: distributed-implementation/preparations/main.cpp.s
.PHONY : distributed-implementation/preparations/main.s

# target to generate assembly for a file
distributed-implementation/preparations/main.cpp.s:
	$(MAKE) -f CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/build.make CMakeFiles/GUT_Manycore_Architectures_MCTS.dir/distributed-implementation/preparations/main.cpp.s
.PHONY : distributed-implementation/preparations/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... GUT_Manycore_Architectures_MCTS"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... distributed-implementation/preparations/MctsNode.o"
	@echo "... distributed-implementation/preparations/MctsNode.i"
	@echo "... distributed-implementation/preparations/MctsNode.s"
	@echo "... distributed-implementation/preparations/MctsNodeDeserializer.o"
	@echo "... distributed-implementation/preparations/MctsNodeDeserializer.i"
	@echo "... distributed-implementation/preparations/MctsNodeDeserializer.s"
	@echo "... distributed-implementation/preparations/MctsNodeSerializer.o"
	@echo "... distributed-implementation/preparations/MctsNodeSerializer.i"
	@echo "... distributed-implementation/preparations/MctsNodeSerializer.s"
	@echo "... distributed-implementation/preparations/MctsTreeMerger.o"
	@echo "... distributed-implementation/preparations/MctsTreeMerger.i"
	@echo "... distributed-implementation/preparations/MctsTreeMerger.s"
	@echo "... distributed-implementation/preparations/NimGameState.o"
	@echo "... distributed-implementation/preparations/NimGameState.i"
	@echo "... distributed-implementation/preparations/NimGameState.s"
	@echo "... distributed-implementation/preparations/UctSortMcts.o"
	@echo "... distributed-implementation/preparations/UctSortMcts.i"
	@echo "... distributed-implementation/preparations/UctSortMcts.s"
	@echo "... distributed-implementation/preparations/main.o"
	@echo "... distributed-implementation/preparations/main.i"
	@echo "... distributed-implementation/preparations/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

