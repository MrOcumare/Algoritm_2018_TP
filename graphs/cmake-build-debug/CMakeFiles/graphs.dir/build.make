# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Mr.ocumare/Desktop/graphs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Mr.ocumare/Desktop/graphs/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/graphs.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/graphs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/graphs.dir/flags.make

CMakeFiles/graphs.dir/main.cpp.o: CMakeFiles/graphs.dir/flags.make
CMakeFiles/graphs.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Mr.ocumare/Desktop/graphs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/graphs.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/graphs.dir/main.cpp.o -c /Users/Mr.ocumare/Desktop/graphs/main.cpp

CMakeFiles/graphs.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphs.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Mr.ocumare/Desktop/graphs/main.cpp > CMakeFiles/graphs.dir/main.cpp.i

CMakeFiles/graphs.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphs.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Mr.ocumare/Desktop/graphs/main.cpp -o CMakeFiles/graphs.dir/main.cpp.s

CMakeFiles/graphs.dir/IGraph.cpp.o: CMakeFiles/graphs.dir/flags.make
CMakeFiles/graphs.dir/IGraph.cpp.o: ../IGraph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Mr.ocumare/Desktop/graphs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/graphs.dir/IGraph.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/graphs.dir/IGraph.cpp.o -c /Users/Mr.ocumare/Desktop/graphs/IGraph.cpp

CMakeFiles/graphs.dir/IGraph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphs.dir/IGraph.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Mr.ocumare/Desktop/graphs/IGraph.cpp > CMakeFiles/graphs.dir/IGraph.cpp.i

CMakeFiles/graphs.dir/IGraph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphs.dir/IGraph.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Mr.ocumare/Desktop/graphs/IGraph.cpp -o CMakeFiles/graphs.dir/IGraph.cpp.s

CMakeFiles/graphs.dir/CListGraph.cpp.o: CMakeFiles/graphs.dir/flags.make
CMakeFiles/graphs.dir/CListGraph.cpp.o: ../CListGraph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Mr.ocumare/Desktop/graphs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/graphs.dir/CListGraph.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/graphs.dir/CListGraph.cpp.o -c /Users/Mr.ocumare/Desktop/graphs/CListGraph.cpp

CMakeFiles/graphs.dir/CListGraph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphs.dir/CListGraph.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Mr.ocumare/Desktop/graphs/CListGraph.cpp > CMakeFiles/graphs.dir/CListGraph.cpp.i

CMakeFiles/graphs.dir/CListGraph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphs.dir/CListGraph.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Mr.ocumare/Desktop/graphs/CListGraph.cpp -o CMakeFiles/graphs.dir/CListGraph.cpp.s

CMakeFiles/graphs.dir/CMatrixGraph.cpp.o: CMakeFiles/graphs.dir/flags.make
CMakeFiles/graphs.dir/CMatrixGraph.cpp.o: ../CMatrixGraph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Mr.ocumare/Desktop/graphs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/graphs.dir/CMatrixGraph.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/graphs.dir/CMatrixGraph.cpp.o -c /Users/Mr.ocumare/Desktop/graphs/CMatrixGraph.cpp

CMakeFiles/graphs.dir/CMatrixGraph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphs.dir/CMatrixGraph.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Mr.ocumare/Desktop/graphs/CMatrixGraph.cpp > CMakeFiles/graphs.dir/CMatrixGraph.cpp.i

CMakeFiles/graphs.dir/CMatrixGraph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphs.dir/CMatrixGraph.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Mr.ocumare/Desktop/graphs/CMatrixGraph.cpp -o CMakeFiles/graphs.dir/CMatrixGraph.cpp.s

CMakeFiles/graphs.dir/CSetGraph.cpp.o: CMakeFiles/graphs.dir/flags.make
CMakeFiles/graphs.dir/CSetGraph.cpp.o: ../CSetGraph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Mr.ocumare/Desktop/graphs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/graphs.dir/CSetGraph.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/graphs.dir/CSetGraph.cpp.o -c /Users/Mr.ocumare/Desktop/graphs/CSetGraph.cpp

CMakeFiles/graphs.dir/CSetGraph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphs.dir/CSetGraph.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Mr.ocumare/Desktop/graphs/CSetGraph.cpp > CMakeFiles/graphs.dir/CSetGraph.cpp.i

CMakeFiles/graphs.dir/CSetGraph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphs.dir/CSetGraph.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Mr.ocumare/Desktop/graphs/CSetGraph.cpp -o CMakeFiles/graphs.dir/CSetGraph.cpp.s

CMakeFiles/graphs.dir/CArcGraph.cpp.o: CMakeFiles/graphs.dir/flags.make
CMakeFiles/graphs.dir/CArcGraph.cpp.o: ../CArcGraph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Mr.ocumare/Desktop/graphs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/graphs.dir/CArcGraph.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/graphs.dir/CArcGraph.cpp.o -c /Users/Mr.ocumare/Desktop/graphs/CArcGraph.cpp

CMakeFiles/graphs.dir/CArcGraph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphs.dir/CArcGraph.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Mr.ocumare/Desktop/graphs/CArcGraph.cpp > CMakeFiles/graphs.dir/CArcGraph.cpp.i

CMakeFiles/graphs.dir/CArcGraph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphs.dir/CArcGraph.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Mr.ocumare/Desktop/graphs/CArcGraph.cpp -o CMakeFiles/graphs.dir/CArcGraph.cpp.s

CMakeFiles/graphs.dir/Generator.cpp.o: CMakeFiles/graphs.dir/flags.make
CMakeFiles/graphs.dir/Generator.cpp.o: ../Generator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Mr.ocumare/Desktop/graphs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/graphs.dir/Generator.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/graphs.dir/Generator.cpp.o -c /Users/Mr.ocumare/Desktop/graphs/Generator.cpp

CMakeFiles/graphs.dir/Generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphs.dir/Generator.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Mr.ocumare/Desktop/graphs/Generator.cpp > CMakeFiles/graphs.dir/Generator.cpp.i

CMakeFiles/graphs.dir/Generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphs.dir/Generator.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Mr.ocumare/Desktop/graphs/Generator.cpp -o CMakeFiles/graphs.dir/Generator.cpp.s

# Object files for target graphs
graphs_OBJECTS = \
"CMakeFiles/graphs.dir/main.cpp.o" \
"CMakeFiles/graphs.dir/IGraph.cpp.o" \
"CMakeFiles/graphs.dir/CListGraph.cpp.o" \
"CMakeFiles/graphs.dir/CMatrixGraph.cpp.o" \
"CMakeFiles/graphs.dir/CSetGraph.cpp.o" \
"CMakeFiles/graphs.dir/CArcGraph.cpp.o" \
"CMakeFiles/graphs.dir/Generator.cpp.o"

# External object files for target graphs
graphs_EXTERNAL_OBJECTS =

graphs: CMakeFiles/graphs.dir/main.cpp.o
graphs: CMakeFiles/graphs.dir/IGraph.cpp.o
graphs: CMakeFiles/graphs.dir/CListGraph.cpp.o
graphs: CMakeFiles/graphs.dir/CMatrixGraph.cpp.o
graphs: CMakeFiles/graphs.dir/CSetGraph.cpp.o
graphs: CMakeFiles/graphs.dir/CArcGraph.cpp.o
graphs: CMakeFiles/graphs.dir/Generator.cpp.o
graphs: CMakeFiles/graphs.dir/build.make
graphs: CMakeFiles/graphs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Mr.ocumare/Desktop/graphs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable graphs"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graphs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/graphs.dir/build: graphs

.PHONY : CMakeFiles/graphs.dir/build

CMakeFiles/graphs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/graphs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/graphs.dir/clean

CMakeFiles/graphs.dir/depend:
	cd /Users/Mr.ocumare/Desktop/graphs/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Mr.ocumare/Desktop/graphs /Users/Mr.ocumare/Desktop/graphs /Users/Mr.ocumare/Desktop/graphs/cmake-build-debug /Users/Mr.ocumare/Desktop/graphs/cmake-build-debug /Users/Mr.ocumare/Desktop/graphs/cmake-build-debug/CMakeFiles/graphs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/graphs.dir/depend

