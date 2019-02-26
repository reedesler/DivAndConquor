# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mabole/Documents/cs436d/team11game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mabole/Documents/cs436d/team11game

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/mabole/Documents/cs436d/team11game/CMakeFiles /home/mabole/Documents/cs436d/team11game/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/mabole/Documents/cs436d/team11game/CMakeFiles 0
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
# Target rules for targets named DivConq

# Build rule for target.
DivConq: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 DivConq
.PHONY : DivConq

# fast build rule for target.
DivConq/fast:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/build
.PHONY : DivConq/fast

src/Button.o: src/Button.cpp.o

.PHONY : src/Button.o

# target to build an object file
src/Button.cpp.o:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Button.cpp.o
.PHONY : src/Button.cpp.o

src/Button.i: src/Button.cpp.i

.PHONY : src/Button.i

# target to preprocess a source file
src/Button.cpp.i:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Button.cpp.i
.PHONY : src/Button.cpp.i

src/Button.s: src/Button.cpp.s

.PHONY : src/Button.s

# target to generate assembly for a file
src/Button.cpp.s:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Button.cpp.s
.PHONY : src/Button.cpp.s

src/Common.o: src/Common.cpp.o

.PHONY : src/Common.o

# target to build an object file
src/Common.cpp.o:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Common.cpp.o
.PHONY : src/Common.cpp.o

src/Common.i: src/Common.cpp.i

.PHONY : src/Common.i

# target to preprocess a source file
src/Common.cpp.i:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Common.cpp.i
.PHONY : src/Common.cpp.i

src/Common.s: src/Common.cpp.s

.PHONY : src/Common.s

# target to generate assembly for a file
src/Common.cpp.s:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Common.cpp.s
.PHONY : src/Common.cpp.s

src/Game.o: src/Game.cpp.o

.PHONY : src/Game.o

# target to build an object file
src/Game.cpp.o:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Game.cpp.o
.PHONY : src/Game.cpp.o

src/Game.i: src/Game.cpp.i

.PHONY : src/Game.i

# target to preprocess a source file
src/Game.cpp.i:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Game.cpp.i
.PHONY : src/Game.cpp.i

src/Game.s: src/Game.cpp.s

.PHONY : src/Game.s

# target to generate assembly for a file
src/Game.cpp.s:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Game.cpp.s
.PHONY : src/Game.cpp.s

src/GameWindow.o: src/GameWindow.cpp.o

.PHONY : src/GameWindow.o

# target to build an object file
src/GameWindow.cpp.o:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/GameWindow.cpp.o
.PHONY : src/GameWindow.cpp.o

src/GameWindow.i: src/GameWindow.cpp.i

.PHONY : src/GameWindow.i

# target to preprocess a source file
src/GameWindow.cpp.i:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/GameWindow.cpp.i
.PHONY : src/GameWindow.cpp.i

src/GameWindow.s: src/GameWindow.cpp.s

.PHONY : src/GameWindow.s

# target to generate assembly for a file
src/GameWindow.cpp.s:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/GameWindow.cpp.s
.PHONY : src/GameWindow.cpp.s

src/Main.o: src/Main.cpp.o

.PHONY : src/Main.o

# target to build an object file
src/Main.cpp.o:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Main.cpp.o
.PHONY : src/Main.cpp.o

src/Main.i: src/Main.cpp.i

.PHONY : src/Main.i

# target to preprocess a source file
src/Main.cpp.i:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Main.cpp.i
.PHONY : src/Main.cpp.i

src/Main.s: src/Main.cpp.s

.PHONY : src/Main.s

# target to generate assembly for a file
src/Main.cpp.s:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Main.cpp.s
.PHONY : src/Main.cpp.s

src/Pirate.o: src/Pirate.cpp.o

.PHONY : src/Pirate.o

# target to build an object file
src/Pirate.cpp.o:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Pirate.cpp.o
.PHONY : src/Pirate.cpp.o

src/Pirate.i: src/Pirate.cpp.i

.PHONY : src/Pirate.i

# target to preprocess a source file
src/Pirate.cpp.i:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Pirate.cpp.i
.PHONY : src/Pirate.cpp.i

src/Pirate.s: src/Pirate.cpp.s

.PHONY : src/Pirate.s

# target to generate assembly for a file
src/Pirate.cpp.s:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Pirate.cpp.s
.PHONY : src/Pirate.cpp.s

src/Sprite.o: src/Sprite.cpp.o

.PHONY : src/Sprite.o

# target to build an object file
src/Sprite.cpp.o:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Sprite.cpp.o
.PHONY : src/Sprite.cpp.o

src/Sprite.i: src/Sprite.cpp.i

.PHONY : src/Sprite.i

# target to preprocess a source file
src/Sprite.cpp.i:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Sprite.cpp.i
.PHONY : src/Sprite.cpp.i

src/Sprite.s: src/Sprite.cpp.s

.PHONY : src/Sprite.s

# target to generate assembly for a file
src/Sprite.cpp.s:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/Sprite.cpp.s
.PHONY : src/Sprite.cpp.s

src/World/Camera.o: src/World/Camera.cpp.o

.PHONY : src/World/Camera.o

# target to build an object file
src/World/Camera.cpp.o:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/Camera.cpp.o
.PHONY : src/World/Camera.cpp.o

src/World/Camera.i: src/World/Camera.cpp.i

.PHONY : src/World/Camera.i

# target to preprocess a source file
src/World/Camera.cpp.i:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/Camera.cpp.i
.PHONY : src/World/Camera.cpp.i

src/World/Camera.s: src/World/Camera.cpp.s

.PHONY : src/World/Camera.s

# target to generate assembly for a file
src/World/Camera.cpp.s:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/Camera.cpp.s
.PHONY : src/World/Camera.cpp.s

src/World/GameObject.o: src/World/GameObject.cpp.o

.PHONY : src/World/GameObject.o

# target to build an object file
src/World/GameObject.cpp.o:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/GameObject.cpp.o
.PHONY : src/World/GameObject.cpp.o

src/World/GameObject.i: src/World/GameObject.cpp.i

.PHONY : src/World/GameObject.i

# target to preprocess a source file
src/World/GameObject.cpp.i:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/GameObject.cpp.i
.PHONY : src/World/GameObject.cpp.i

src/World/GameObject.s: src/World/GameObject.cpp.s

.PHONY : src/World/GameObject.s

# target to generate assembly for a file
src/World/GameObject.cpp.s:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/GameObject.cpp.s
.PHONY : src/World/GameObject.cpp.s

src/World/Pathfinder.o: src/World/Pathfinder.cpp.o

.PHONY : src/World/Pathfinder.o

# target to build an object file
src/World/Pathfinder.cpp.o:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/Pathfinder.cpp.o
.PHONY : src/World/Pathfinder.cpp.o

src/World/Pathfinder.i: src/World/Pathfinder.cpp.i

.PHONY : src/World/Pathfinder.i

# target to preprocess a source file
src/World/Pathfinder.cpp.i:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/Pathfinder.cpp.i
.PHONY : src/World/Pathfinder.cpp.i

src/World/Pathfinder.s: src/World/Pathfinder.cpp.s

.PHONY : src/World/Pathfinder.s

# target to generate assembly for a file
src/World/Pathfinder.cpp.s:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/Pathfinder.cpp.s
.PHONY : src/World/Pathfinder.cpp.s

src/World/ShipObject.o: src/World/ShipObject.cpp.o

.PHONY : src/World/ShipObject.o

# target to build an object file
src/World/ShipObject.cpp.o:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/ShipObject.cpp.o
.PHONY : src/World/ShipObject.cpp.o

src/World/ShipObject.i: src/World/ShipObject.cpp.i

.PHONY : src/World/ShipObject.i

# target to preprocess a source file
src/World/ShipObject.cpp.i:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/ShipObject.cpp.i
.PHONY : src/World/ShipObject.cpp.i

src/World/ShipObject.s: src/World/ShipObject.cpp.s

.PHONY : src/World/ShipObject.s

# target to generate assembly for a file
src/World/ShipObject.cpp.s:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/ShipObject.cpp.s
.PHONY : src/World/ShipObject.cpp.s

src/World/Tilemap.o: src/World/Tilemap.cpp.o

.PHONY : src/World/Tilemap.o

# target to build an object file
src/World/Tilemap.cpp.o:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/Tilemap.cpp.o
.PHONY : src/World/Tilemap.cpp.o

src/World/Tilemap.i: src/World/Tilemap.cpp.i

.PHONY : src/World/Tilemap.i

# target to preprocess a source file
src/World/Tilemap.cpp.i:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/Tilemap.cpp.i
.PHONY : src/World/Tilemap.cpp.i

src/World/Tilemap.s: src/World/Tilemap.cpp.s

.PHONY : src/World/Tilemap.s

# target to generate assembly for a file
src/World/Tilemap.cpp.s:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/Tilemap.cpp.s
.PHONY : src/World/Tilemap.cpp.s

src/World/World.o: src/World/World.cpp.o

.PHONY : src/World/World.o

# target to build an object file
src/World/World.cpp.o:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/World.cpp.o
.PHONY : src/World/World.cpp.o

src/World/World.i: src/World/World.cpp.i

.PHONY : src/World/World.i

# target to preprocess a source file
src/World/World.cpp.i:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/World.cpp.i
.PHONY : src/World/World.cpp.i

src/World/World.s: src/World/World.cpp.s

.PHONY : src/World/World.s

# target to generate assembly for a file
src/World/World.cpp.s:
	$(MAKE) -f CMakeFiles/DivConq.dir/build.make CMakeFiles/DivConq.dir/src/World/World.cpp.s
.PHONY : src/World/World.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... DivConq"
	@echo "... edit_cache"
	@echo "... src/Button.o"
	@echo "... src/Button.i"
	@echo "... src/Button.s"
	@echo "... src/Common.o"
	@echo "... src/Common.i"
	@echo "... src/Common.s"
	@echo "... src/Game.o"
	@echo "... src/Game.i"
	@echo "... src/Game.s"
	@echo "... src/GameWindow.o"
	@echo "... src/GameWindow.i"
	@echo "... src/GameWindow.s"
	@echo "... src/Main.o"
	@echo "... src/Main.i"
	@echo "... src/Main.s"
	@echo "... src/Pirate.o"
	@echo "... src/Pirate.i"
	@echo "... src/Pirate.s"
	@echo "... src/Sprite.o"
	@echo "... src/Sprite.i"
	@echo "... src/Sprite.s"
	@echo "... src/World/Camera.o"
	@echo "... src/World/Camera.i"
	@echo "... src/World/Camera.s"
	@echo "... src/World/GameObject.o"
	@echo "... src/World/GameObject.i"
	@echo "... src/World/GameObject.s"
	@echo "... src/World/Pathfinder.o"
	@echo "... src/World/Pathfinder.i"
	@echo "... src/World/Pathfinder.s"
	@echo "... src/World/ShipObject.o"
	@echo "... src/World/ShipObject.i"
	@echo "... src/World/ShipObject.s"
	@echo "... src/World/Tilemap.o"
	@echo "... src/World/Tilemap.i"
	@echo "... src/World/Tilemap.s"
	@echo "... src/World/World.o"
	@echo "... src/World/World.i"
	@echo "... src/World/World.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
