# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /c/gardn/client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /c/gardn/client/build

# Include any dependencies generated for this target.
include CMakeFiles/gardn-client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/gardn-client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gardn-client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gardn-client.dir/flags.make

CMakeFiles/gardn-client.dir/Game.cc.obj: CMakeFiles/gardn-client.dir/flags.make
CMakeFiles/gardn-client.dir/Game.cc.obj: /c/gardn/client/Game.cc
CMakeFiles/gardn-client.dir/Game.cc.obj: CMakeFiles/gardn-client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/c/gardn/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gardn-client.dir/Game.cc.obj"
	em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gardn-client.dir/Game.cc.obj -MF CMakeFiles/gardn-client.dir/Game.cc.obj.d -o CMakeFiles/gardn-client.dir/Game.cc.obj -c /c/gardn/client/Game.cc

CMakeFiles/gardn-client.dir/Game.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gardn-client.dir/Game.cc.i"
	em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /c/gardn/client/Game.cc > CMakeFiles/gardn-client.dir/Game.cc.i

CMakeFiles/gardn-client.dir/Game.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gardn-client.dir/Game.cc.s"
	em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /c/gardn/client/Game.cc -o CMakeFiles/gardn-client.dir/Game.cc.s

CMakeFiles/gardn-client.dir/Main.cc.obj: CMakeFiles/gardn-client.dir/flags.make
CMakeFiles/gardn-client.dir/Main.cc.obj: /c/gardn/client/Main.cc
CMakeFiles/gardn-client.dir/Main.cc.obj: CMakeFiles/gardn-client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/c/gardn/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/gardn-client.dir/Main.cc.obj"
	em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gardn-client.dir/Main.cc.obj -MF CMakeFiles/gardn-client.dir/Main.cc.obj.d -o CMakeFiles/gardn-client.dir/Main.cc.obj -c /c/gardn/client/Main.cc

CMakeFiles/gardn-client.dir/Main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gardn-client.dir/Main.cc.i"
	em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /c/gardn/client/Main.cc > CMakeFiles/gardn-client.dir/Main.cc.i

CMakeFiles/gardn-client.dir/Main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gardn-client.dir/Main.cc.s"
	em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /c/gardn/client/Main.cc -o CMakeFiles/gardn-client.dir/Main.cc.s

CMakeFiles/gardn-client.dir/Renderer.cc.obj: CMakeFiles/gardn-client.dir/flags.make
CMakeFiles/gardn-client.dir/Renderer.cc.obj: /c/gardn/client/Renderer.cc
CMakeFiles/gardn-client.dir/Renderer.cc.obj: CMakeFiles/gardn-client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/c/gardn/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/gardn-client.dir/Renderer.cc.obj"
	em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gardn-client.dir/Renderer.cc.obj -MF CMakeFiles/gardn-client.dir/Renderer.cc.obj.d -o CMakeFiles/gardn-client.dir/Renderer.cc.obj -c /c/gardn/client/Renderer.cc

CMakeFiles/gardn-client.dir/Renderer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gardn-client.dir/Renderer.cc.i"
	em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /c/gardn/client/Renderer.cc > CMakeFiles/gardn-client.dir/Renderer.cc.i

CMakeFiles/gardn-client.dir/Renderer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gardn-client.dir/Renderer.cc.s"
	em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /c/gardn/client/Renderer.cc -o CMakeFiles/gardn-client.dir/Renderer.cc.s

# Object files for target gardn-client
gardn__client_OBJECTS = \
"CMakeFiles/gardn-client.dir/Game.cc.obj" \
"CMakeFiles/gardn-client.dir/Main.cc.obj" \
"CMakeFiles/gardn-client.dir/Renderer.cc.obj"

# External object files for target gardn-client
gardn__client_EXTERNAL_OBJECTS =

gardn-client: CMakeFiles/gardn-client.dir/Game.cc.obj
gardn-client: CMakeFiles/gardn-client.dir/Main.cc.obj
gardn-client: CMakeFiles/gardn-client.dir/Renderer.cc.obj
gardn-client: CMakeFiles/gardn-client.dir/build.make
gardn-client: CMakeFiles/gardn-client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/c/gardn/client/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable gardn-client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gardn-client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gardn-client.dir/build: gardn-client
.PHONY : CMakeFiles/gardn-client.dir/build

CMakeFiles/gardn-client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gardn-client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gardn-client.dir/clean

CMakeFiles/gardn-client.dir/depend:
	cd /c/gardn/client/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /c/gardn/client /c/gardn/client /c/gardn/client/build /c/gardn/client/build /c/gardn/client/build/CMakeFiles/gardn-client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gardn-client.dir/depend

