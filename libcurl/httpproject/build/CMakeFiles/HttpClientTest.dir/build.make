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
CMAKE_SOURCE_DIR = /home/xmf/myTechnical/libcurl/httpproject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xmf/myTechnical/libcurl/httpproject/build

# Include any dependencies generated for this target.
include CMakeFiles/HttpClientTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HttpClientTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HttpClientTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HttpClientTest.dir/flags.make

CMakeFiles/HttpClientTest.dir/HttpClient.cpp.o: CMakeFiles/HttpClientTest.dir/flags.make
CMakeFiles/HttpClientTest.dir/HttpClient.cpp.o: ../HttpClient.cpp
CMakeFiles/HttpClientTest.dir/HttpClient.cpp.o: CMakeFiles/HttpClientTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xmf/myTechnical/libcurl/httpproject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HttpClientTest.dir/HttpClient.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HttpClientTest.dir/HttpClient.cpp.o -MF CMakeFiles/HttpClientTest.dir/HttpClient.cpp.o.d -o CMakeFiles/HttpClientTest.dir/HttpClient.cpp.o -c /home/xmf/myTechnical/libcurl/httpproject/HttpClient.cpp

CMakeFiles/HttpClientTest.dir/HttpClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HttpClientTest.dir/HttpClient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xmf/myTechnical/libcurl/httpproject/HttpClient.cpp > CMakeFiles/HttpClientTest.dir/HttpClient.cpp.i

CMakeFiles/HttpClientTest.dir/HttpClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HttpClientTest.dir/HttpClient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xmf/myTechnical/libcurl/httpproject/HttpClient.cpp -o CMakeFiles/HttpClientTest.dir/HttpClient.cpp.s

CMakeFiles/HttpClientTest.dir/main.cpp.o: CMakeFiles/HttpClientTest.dir/flags.make
CMakeFiles/HttpClientTest.dir/main.cpp.o: ../main.cpp
CMakeFiles/HttpClientTest.dir/main.cpp.o: CMakeFiles/HttpClientTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xmf/myTechnical/libcurl/httpproject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/HttpClientTest.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HttpClientTest.dir/main.cpp.o -MF CMakeFiles/HttpClientTest.dir/main.cpp.o.d -o CMakeFiles/HttpClientTest.dir/main.cpp.o -c /home/xmf/myTechnical/libcurl/httpproject/main.cpp

CMakeFiles/HttpClientTest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HttpClientTest.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xmf/myTechnical/libcurl/httpproject/main.cpp > CMakeFiles/HttpClientTest.dir/main.cpp.i

CMakeFiles/HttpClientTest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HttpClientTest.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xmf/myTechnical/libcurl/httpproject/main.cpp -o CMakeFiles/HttpClientTest.dir/main.cpp.s

# Object files for target HttpClientTest
HttpClientTest_OBJECTS = \
"CMakeFiles/HttpClientTest.dir/HttpClient.cpp.o" \
"CMakeFiles/HttpClientTest.dir/main.cpp.o"

# External object files for target HttpClientTest
HttpClientTest_EXTERNAL_OBJECTS =

HttpClientTest: CMakeFiles/HttpClientTest.dir/HttpClient.cpp.o
HttpClientTest: CMakeFiles/HttpClientTest.dir/main.cpp.o
HttpClientTest: CMakeFiles/HttpClientTest.dir/build.make
HttpClientTest: /usr/lib/x86_64-linux-gnu/libcurl.so
HttpClientTest: CMakeFiles/HttpClientTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xmf/myTechnical/libcurl/httpproject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable HttpClientTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HttpClientTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HttpClientTest.dir/build: HttpClientTest
.PHONY : CMakeFiles/HttpClientTest.dir/build

CMakeFiles/HttpClientTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HttpClientTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HttpClientTest.dir/clean

CMakeFiles/HttpClientTest.dir/depend:
	cd /home/xmf/myTechnical/libcurl/httpproject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xmf/myTechnical/libcurl/httpproject /home/xmf/myTechnical/libcurl/httpproject /home/xmf/myTechnical/libcurl/httpproject/build /home/xmf/myTechnical/libcurl/httpproject/build /home/xmf/myTechnical/libcurl/httpproject/build/CMakeFiles/HttpClientTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HttpClientTest.dir/depend

