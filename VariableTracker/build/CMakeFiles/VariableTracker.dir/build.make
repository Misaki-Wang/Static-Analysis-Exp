# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/misaki/Documents/sa/VariableTracker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/misaki/Documents/sa/VariableTracker/build

# Include any dependencies generated for this target.
include CMakeFiles/VariableTracker.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/VariableTracker.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/VariableTracker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VariableTracker.dir/flags.make

CMakeFiles/VariableTracker.dir/VariableTracker.cpp.o: CMakeFiles/VariableTracker.dir/flags.make
CMakeFiles/VariableTracker.dir/VariableTracker.cpp.o: ../VariableTracker.cpp
CMakeFiles/VariableTracker.dir/VariableTracker.cpp.o: CMakeFiles/VariableTracker.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/misaki/Documents/sa/VariableTracker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VariableTracker.dir/VariableTracker.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/VariableTracker.dir/VariableTracker.cpp.o -MF CMakeFiles/VariableTracker.dir/VariableTracker.cpp.o.d -o CMakeFiles/VariableTracker.dir/VariableTracker.cpp.o -c /home/misaki/Documents/sa/VariableTracker/VariableTracker.cpp

CMakeFiles/VariableTracker.dir/VariableTracker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VariableTracker.dir/VariableTracker.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/misaki/Documents/sa/VariableTracker/VariableTracker.cpp > CMakeFiles/VariableTracker.dir/VariableTracker.cpp.i

CMakeFiles/VariableTracker.dir/VariableTracker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VariableTracker.dir/VariableTracker.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/misaki/Documents/sa/VariableTracker/VariableTracker.cpp -o CMakeFiles/VariableTracker.dir/VariableTracker.cpp.s

# Object files for target VariableTracker
VariableTracker_OBJECTS = \
"CMakeFiles/VariableTracker.dir/VariableTracker.cpp.o"

# External object files for target VariableTracker
VariableTracker_EXTERNAL_OBJECTS =

libVariableTracker.so: CMakeFiles/VariableTracker.dir/VariableTracker.cpp.o
libVariableTracker.so: CMakeFiles/VariableTracker.dir/build.make
libVariableTracker.so: CMakeFiles/VariableTracker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/misaki/Documents/sa/VariableTracker/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libVariableTracker.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VariableTracker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VariableTracker.dir/build: libVariableTracker.so
.PHONY : CMakeFiles/VariableTracker.dir/build

CMakeFiles/VariableTracker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VariableTracker.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VariableTracker.dir/clean

CMakeFiles/VariableTracker.dir/depend:
	cd /home/misaki/Documents/sa/VariableTracker/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/misaki/Documents/sa/VariableTracker /home/misaki/Documents/sa/VariableTracker /home/misaki/Documents/sa/VariableTracker/build /home/misaki/Documents/sa/VariableTracker/build /home/misaki/Documents/sa/VariableTracker/build/CMakeFiles/VariableTracker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VariableTracker.dir/depend

