# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/zhacgsn/VSProjects/tinyxml2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zhacgsn/VSProjects/tinyxml2/build

# Include any dependencies generated for this target.
include CMakeFiles/xmltest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/xmltest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/xmltest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/xmltest.dir/flags.make

CMakeFiles/xmltest.dir/xmltest.cpp.o: CMakeFiles/xmltest.dir/flags.make
CMakeFiles/xmltest.dir/xmltest.cpp.o: /Users/zhacgsn/VSProjects/tinyxml2/xmltest.cpp
CMakeFiles/xmltest.dir/xmltest.cpp.o: CMakeFiles/xmltest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zhacgsn/VSProjects/tinyxml2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/xmltest.dir/xmltest.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/xmltest.dir/xmltest.cpp.o -MF CMakeFiles/xmltest.dir/xmltest.cpp.o.d -o CMakeFiles/xmltest.dir/xmltest.cpp.o -c /Users/zhacgsn/VSProjects/tinyxml2/xmltest.cpp

CMakeFiles/xmltest.dir/xmltest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/xmltest.dir/xmltest.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhacgsn/VSProjects/tinyxml2/xmltest.cpp > CMakeFiles/xmltest.dir/xmltest.cpp.i

CMakeFiles/xmltest.dir/xmltest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/xmltest.dir/xmltest.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhacgsn/VSProjects/tinyxml2/xmltest.cpp -o CMakeFiles/xmltest.dir/xmltest.cpp.s

# Object files for target xmltest
xmltest_OBJECTS = \
"CMakeFiles/xmltest.dir/xmltest.cpp.o"

# External object files for target xmltest
xmltest_EXTERNAL_OBJECTS =

xmltest: CMakeFiles/xmltest.dir/xmltest.cpp.o
xmltest: CMakeFiles/xmltest.dir/build.make
xmltest: libtinyxml2.a
xmltest: CMakeFiles/xmltest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/zhacgsn/VSProjects/tinyxml2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable xmltest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/xmltest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/xmltest.dir/build: xmltest
.PHONY : CMakeFiles/xmltest.dir/build

CMakeFiles/xmltest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/xmltest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/xmltest.dir/clean

CMakeFiles/xmltest.dir/depend:
	cd /Users/zhacgsn/VSProjects/tinyxml2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zhacgsn/VSProjects/tinyxml2 /Users/zhacgsn/VSProjects/tinyxml2 /Users/zhacgsn/VSProjects/tinyxml2/build /Users/zhacgsn/VSProjects/tinyxml2/build /Users/zhacgsn/VSProjects/tinyxml2/build/CMakeFiles/xmltest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/xmltest.dir/depend
