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
CMAKE_SOURCE_DIR = D:\ass

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\ass\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ass.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ass.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ass.dir/flags.make

CMakeFiles/ass.dir/main.c.obj: CMakeFiles/ass.dir/flags.make
CMakeFiles/ass.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\ass\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ass.dir/main.c.obj"
	C:\PROGRA~2\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\ass.dir\main.c.obj   -c D:\ass\main.c

CMakeFiles/ass.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ass.dir/main.c.i"
	C:\PROGRA~2\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\ass\main.c > CMakeFiles\ass.dir\main.c.i

CMakeFiles/ass.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ass.dir/main.c.s"
	C:\PROGRA~2\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\ass\main.c -o CMakeFiles\ass.dir\main.c.s

# Object files for target ass
ass_OBJECTS = \
"CMakeFiles/ass.dir/main.c.obj"

# External object files for target ass
ass_EXTERNAL_OBJECTS =

ass.exe: CMakeFiles/ass.dir/main.c.obj
ass.exe: CMakeFiles/ass.dir/build.make
ass.exe: CMakeFiles/ass.dir/linklibs.rsp
ass.exe: CMakeFiles/ass.dir/objects1.rsp
ass.exe: CMakeFiles/ass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\ass\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ass.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ass.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ass.dir/build: ass.exe

.PHONY : CMakeFiles/ass.dir/build

CMakeFiles/ass.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ass.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ass.dir/clean

CMakeFiles/ass.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\ass D:\ass D:\ass\cmake-build-debug D:\ass\cmake-build-debug D:\ass\cmake-build-debug\CMakeFiles\ass.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ass.dir/depend

