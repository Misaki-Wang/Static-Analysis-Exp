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
CMAKE_SOURCE_DIR = /home/misaki/Documents/sa/OpcodeCounter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/misaki/Documents/sa/OpcodeCounter/build

# Include any dependencies generated for this target.
include CMakeFiles/OpcodeCounter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OpcodeCounter.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OpcodeCounter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpcodeCounter.dir/flags.make

CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.o: CMakeFiles/OpcodeCounter.dir/flags.make
CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.o: ../OpcodeCounter.cpp
CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.o: CMakeFiles/OpcodeCounter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/misaki/Documents/sa/OpcodeCounter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.o -MF CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.o.d -o CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.o -c /home/misaki/Documents/sa/OpcodeCounter/OpcodeCounter.cpp

CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/misaki/Documents/sa/OpcodeCounter/OpcodeCounter.cpp > CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.i

CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/misaki/Documents/sa/OpcodeCounter/OpcodeCounter.cpp -o CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.s

# Object files for target OpcodeCounter
OpcodeCounter_OBJECTS = \
"CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.o"

# External object files for target OpcodeCounter
OpcodeCounter_EXTERNAL_OBJECTS =

libOpcodeCounter.so: CMakeFiles/OpcodeCounter.dir/OpcodeCounter.cpp.o
libOpcodeCounter.so: CMakeFiles/OpcodeCounter.dir/build.make
libOpcodeCounter.so: CMakeFiles/OpcodeCounter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/misaki/Documents/sa/OpcodeCounter/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libOpcodeCounter.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpcodeCounter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpcodeCounter.dir/build: libOpcodeCounter.so
.PHONY : CMakeFiles/OpcodeCounter.dir/build

CMakeFiles/OpcodeCounter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpcodeCounter.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpcodeCounter.dir/clean

CMakeFiles/OpcodeCounter.dir/depend:
	cd /home/misaki/Documents/sa/OpcodeCounter/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/misaki/Documents/sa/OpcodeCounter /home/misaki/Documents/sa/OpcodeCounter /home/misaki/Documents/sa/OpcodeCounter/build /home/misaki/Documents/sa/OpcodeCounter/build /home/misaki/Documents/sa/OpcodeCounter/build/CMakeFiles/OpcodeCounter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpcodeCounter.dir/depend

