# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\CLion\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\CLion\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\ass2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\ass2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ass2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ass2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ass2.dir/flags.make

CMakeFiles/ass2.dir/MyAVLTree.c.obj: CMakeFiles/ass2.dir/flags.make
CMakeFiles/ass2.dir/MyAVLTree.c.obj: ../MyAVLTree.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ass2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ass2.dir/MyAVLTree.c.obj"
	C:\PROGRA~2\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\ass2.dir\MyAVLTree.c.obj   -c D:\ass2\MyAVLTree.c

CMakeFiles/ass2.dir/MyAVLTree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ass2.dir/MyAVLTree.c.i"
	C:\PROGRA~2\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\ass2\MyAVLTree.c > CMakeFiles\ass2.dir\MyAVLTree.c.i

CMakeFiles/ass2.dir/MyAVLTree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ass2.dir/MyAVLTree.c.s"
	C:\PROGRA~2\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\ass2\MyAVLTree.c -o CMakeFiles\ass2.dir\MyAVLTree.c.s

# Object files for target ass2
ass2_OBJECTS = \
"CMakeFiles/ass2.dir/MyAVLTree.c.obj"

# External object files for target ass2
ass2_EXTERNAL_OBJECTS =

ass2.exe: CMakeFiles/ass2.dir/MyAVLTree.c.obj
ass2.exe: CMakeFiles/ass2.dir/build.make
ass2.exe: CMakeFiles/ass2.dir/linklibs.rsp
ass2.exe: CMakeFiles/ass2.dir/objects1.rsp
ass2.exe: CMakeFiles/ass2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\ass2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ass2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ass2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ass2.dir/build: ass2.exe

.PHONY : CMakeFiles/ass2.dir/build

CMakeFiles/ass2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ass2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ass2.dir/clean

CMakeFiles/ass2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\ass2 D:\ass2 D:\ass2\cmake-build-debug D:\ass2\cmake-build-debug D:\ass2\cmake-build-debug\CMakeFiles\ass2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ass2.dir/depend

