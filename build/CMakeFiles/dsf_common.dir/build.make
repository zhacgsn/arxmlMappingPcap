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
CMAKE_SOURCE_DIR = /Users/zhacgsn/VSProjects/arxml-mapping-pcap

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/zhacgsn/VSProjects/arxml-mapping-pcap/build

# Include any dependencies generated for this target.
include CMakeFiles/dsf_common.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/dsf_common.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dsf_common.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dsf_common.dir/flags.make

CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.o: CMakeFiles/dsf_common.dir/flags.make
CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.o: /Users/zhacgsn/VSProjects/arxml-mapping-pcap/DSFCommon/dsftime.cpp
CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.o: CMakeFiles/dsf_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/zhacgsn/VSProjects/arxml-mapping-pcap/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.o -MF CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.o.d -o CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.o -c /Users/zhacgsn/VSProjects/arxml-mapping-pcap/DSFCommon/dsftime.cpp

CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/zhacgsn/VSProjects/arxml-mapping-pcap/DSFCommon/dsftime.cpp > CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.i

CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/zhacgsn/VSProjects/arxml-mapping-pcap/DSFCommon/dsftime.cpp -o CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.s

# Object files for target dsf_common
dsf_common_OBJECTS = \
"CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.o"

# External object files for target dsf_common
dsf_common_EXTERNAL_OBJECTS =

libdsf_common.a: CMakeFiles/dsf_common.dir/DSFCommon/dsftime.cpp.o
libdsf_common.a: CMakeFiles/dsf_common.dir/build.make
libdsf_common.a: CMakeFiles/dsf_common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/zhacgsn/VSProjects/arxml-mapping-pcap/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libdsf_common.a"
	$(CMAKE_COMMAND) -P CMakeFiles/dsf_common.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dsf_common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dsf_common.dir/build: libdsf_common.a
.PHONY : CMakeFiles/dsf_common.dir/build

CMakeFiles/dsf_common.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dsf_common.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dsf_common.dir/clean

CMakeFiles/dsf_common.dir/depend:
	cd /Users/zhacgsn/VSProjects/arxml-mapping-pcap/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/zhacgsn/VSProjects/arxml-mapping-pcap /Users/zhacgsn/VSProjects/arxml-mapping-pcap /Users/zhacgsn/VSProjects/arxml-mapping-pcap/build /Users/zhacgsn/VSProjects/arxml-mapping-pcap/build /Users/zhacgsn/VSProjects/arxml-mapping-pcap/build/CMakeFiles/dsf_common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dsf_common.dir/depend
