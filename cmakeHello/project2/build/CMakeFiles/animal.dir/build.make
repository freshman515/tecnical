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
CMAKE_SOURCE_DIR = /home/xmf/myTechnical/cmakeHello/project2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xmf/myTechnical/cmakeHello/project2/build

# Include any dependencies generated for this target.
include CMakeFiles/animal.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/animal.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/animal.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/animal.dir/flags.make

CMakeFiles/animal.dir/main.cpp.o: CMakeFiles/animal.dir/flags.make
CMakeFiles/animal.dir/main.cpp.o: ../main.cpp
CMakeFiles/animal.dir/main.cpp.o: CMakeFiles/animal.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xmf/myTechnical/cmakeHello/project2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/animal.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/animal.dir/main.cpp.o -MF CMakeFiles/animal.dir/main.cpp.o.d -o CMakeFiles/animal.dir/main.cpp.o -c /home/xmf/myTechnical/cmakeHello/project2/main.cpp

CMakeFiles/animal.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/animal.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xmf/myTechnical/cmakeHello/project2/main.cpp > CMakeFiles/animal.dir/main.cpp.i

CMakeFiles/animal.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/animal.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xmf/myTechnical/cmakeHello/project2/main.cpp -o CMakeFiles/animal.dir/main.cpp.s

CMakeFiles/animal.dir/animal/cat.cpp.o: CMakeFiles/animal.dir/flags.make
CMakeFiles/animal.dir/animal/cat.cpp.o: ../animal/cat.cpp
CMakeFiles/animal.dir/animal/cat.cpp.o: CMakeFiles/animal.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xmf/myTechnical/cmakeHello/project2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/animal.dir/animal/cat.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/animal.dir/animal/cat.cpp.o -MF CMakeFiles/animal.dir/animal/cat.cpp.o.d -o CMakeFiles/animal.dir/animal/cat.cpp.o -c /home/xmf/myTechnical/cmakeHello/project2/animal/cat.cpp

CMakeFiles/animal.dir/animal/cat.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/animal.dir/animal/cat.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xmf/myTechnical/cmakeHello/project2/animal/cat.cpp > CMakeFiles/animal.dir/animal/cat.cpp.i

CMakeFiles/animal.dir/animal/cat.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/animal.dir/animal/cat.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xmf/myTechnical/cmakeHello/project2/animal/cat.cpp -o CMakeFiles/animal.dir/animal/cat.cpp.s

CMakeFiles/animal.dir/animal/dog.cpp.o: CMakeFiles/animal.dir/flags.make
CMakeFiles/animal.dir/animal/dog.cpp.o: ../animal/dog.cpp
CMakeFiles/animal.dir/animal/dog.cpp.o: CMakeFiles/animal.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xmf/myTechnical/cmakeHello/project2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/animal.dir/animal/dog.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/animal.dir/animal/dog.cpp.o -MF CMakeFiles/animal.dir/animal/dog.cpp.o.d -o CMakeFiles/animal.dir/animal/dog.cpp.o -c /home/xmf/myTechnical/cmakeHello/project2/animal/dog.cpp

CMakeFiles/animal.dir/animal/dog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/animal.dir/animal/dog.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xmf/myTechnical/cmakeHello/project2/animal/dog.cpp > CMakeFiles/animal.dir/animal/dog.cpp.i

CMakeFiles/animal.dir/animal/dog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/animal.dir/animal/dog.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xmf/myTechnical/cmakeHello/project2/animal/dog.cpp -o CMakeFiles/animal.dir/animal/dog.cpp.s

# Object files for target animal
animal_OBJECTS = \
"CMakeFiles/animal.dir/main.cpp.o" \
"CMakeFiles/animal.dir/animal/cat.cpp.o" \
"CMakeFiles/animal.dir/animal/dog.cpp.o"

# External object files for target animal
animal_EXTERNAL_OBJECTS =

animal: CMakeFiles/animal.dir/main.cpp.o
animal: CMakeFiles/animal.dir/animal/cat.cpp.o
animal: CMakeFiles/animal.dir/animal/dog.cpp.o
animal: CMakeFiles/animal.dir/build.make
animal: CMakeFiles/animal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xmf/myTechnical/cmakeHello/project2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable animal"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/animal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/animal.dir/build: animal
.PHONY : CMakeFiles/animal.dir/build

CMakeFiles/animal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/animal.dir/cmake_clean.cmake
.PHONY : CMakeFiles/animal.dir/clean

CMakeFiles/animal.dir/depend:
	cd /home/xmf/myTechnical/cmakeHello/project2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xmf/myTechnical/cmakeHello/project2 /home/xmf/myTechnical/cmakeHello/project2 /home/xmf/myTechnical/cmakeHello/project2/build /home/xmf/myTechnical/cmakeHello/project2/build /home/xmf/myTechnical/cmakeHello/project2/build/CMakeFiles/animal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/animal.dir/depend

