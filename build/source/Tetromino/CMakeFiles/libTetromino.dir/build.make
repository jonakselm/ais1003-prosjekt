# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jonaksel/Documents/Programming/AIS1003-prosjekt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jonaksel/Documents/Programming/AIS1003-prosjekt/build

# Include any dependencies generated for this target.
include source/Tetromino/CMakeFiles/libTetromino.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include source/Tetromino/CMakeFiles/libTetromino.dir/compiler_depend.make

# Include the progress variables for this target.
include source/Tetromino/CMakeFiles/libTetromino.dir/progress.make

# Include the compile flags for this target's objects.
include source/Tetromino/CMakeFiles/libTetromino.dir/flags.make

source/Tetromino/CMakeFiles/libTetromino.dir/Tetromino.cpp.o: source/Tetromino/CMakeFiles/libTetromino.dir/flags.make
source/Tetromino/CMakeFiles/libTetromino.dir/Tetromino.cpp.o: /home/jonaksel/Documents/Programming/AIS1003-prosjekt/source/Tetromino/Tetromino.cpp
source/Tetromino/CMakeFiles/libTetromino.dir/Tetromino.cpp.o: source/Tetromino/CMakeFiles/libTetromino.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/jonaksel/Documents/Programming/AIS1003-prosjekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/Tetromino/CMakeFiles/libTetromino.dir/Tetromino.cpp.o"
	cd /home/jonaksel/Documents/Programming/AIS1003-prosjekt/build/source/Tetromino && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT source/Tetromino/CMakeFiles/libTetromino.dir/Tetromino.cpp.o -MF CMakeFiles/libTetromino.dir/Tetromino.cpp.o.d -o CMakeFiles/libTetromino.dir/Tetromino.cpp.o -c /home/jonaksel/Documents/Programming/AIS1003-prosjekt/source/Tetromino/Tetromino.cpp

source/Tetromino/CMakeFiles/libTetromino.dir/Tetromino.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/libTetromino.dir/Tetromino.cpp.i"
	cd /home/jonaksel/Documents/Programming/AIS1003-prosjekt/build/source/Tetromino && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jonaksel/Documents/Programming/AIS1003-prosjekt/source/Tetromino/Tetromino.cpp > CMakeFiles/libTetromino.dir/Tetromino.cpp.i

source/Tetromino/CMakeFiles/libTetromino.dir/Tetromino.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/libTetromino.dir/Tetromino.cpp.s"
	cd /home/jonaksel/Documents/Programming/AIS1003-prosjekt/build/source/Tetromino && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jonaksel/Documents/Programming/AIS1003-prosjekt/source/Tetromino/Tetromino.cpp -o CMakeFiles/libTetromino.dir/Tetromino.cpp.s

# Object files for target libTetromino
libTetromino_OBJECTS = \
"CMakeFiles/libTetromino.dir/Tetromino.cpp.o"

# External object files for target libTetromino
libTetromino_EXTERNAL_OBJECTS =

source/Tetromino/liblibTetromino.a: source/Tetromino/CMakeFiles/libTetromino.dir/Tetromino.cpp.o
source/Tetromino/liblibTetromino.a: source/Tetromino/CMakeFiles/libTetromino.dir/build.make
source/Tetromino/liblibTetromino.a: source/Tetromino/CMakeFiles/libTetromino.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/jonaksel/Documents/Programming/AIS1003-prosjekt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblibTetromino.a"
	cd /home/jonaksel/Documents/Programming/AIS1003-prosjekt/build/source/Tetromino && $(CMAKE_COMMAND) -P CMakeFiles/libTetromino.dir/cmake_clean_target.cmake
	cd /home/jonaksel/Documents/Programming/AIS1003-prosjekt/build/source/Tetromino && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libTetromino.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/Tetromino/CMakeFiles/libTetromino.dir/build: source/Tetromino/liblibTetromino.a
.PHONY : source/Tetromino/CMakeFiles/libTetromino.dir/build

source/Tetromino/CMakeFiles/libTetromino.dir/clean:
	cd /home/jonaksel/Documents/Programming/AIS1003-prosjekt/build/source/Tetromino && $(CMAKE_COMMAND) -P CMakeFiles/libTetromino.dir/cmake_clean.cmake
.PHONY : source/Tetromino/CMakeFiles/libTetromino.dir/clean

source/Tetromino/CMakeFiles/libTetromino.dir/depend:
	cd /home/jonaksel/Documents/Programming/AIS1003-prosjekt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jonaksel/Documents/Programming/AIS1003-prosjekt /home/jonaksel/Documents/Programming/AIS1003-prosjekt/source/Tetromino /home/jonaksel/Documents/Programming/AIS1003-prosjekt/build /home/jonaksel/Documents/Programming/AIS1003-prosjekt/build/source/Tetromino /home/jonaksel/Documents/Programming/AIS1003-prosjekt/build/source/Tetromino/CMakeFiles/libTetromino.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : source/Tetromino/CMakeFiles/libTetromino.dir/depend

