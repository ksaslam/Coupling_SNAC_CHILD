# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /opt/local/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl

# Utility rule file for NightlyMemCheck.

# Include the progress variables for this target.
include testing/CMakeFiles/NightlyMemCheck.dir/progress.make

testing/CMakeFiles/NightlyMemCheck:
	cd /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing && /opt/local/bin/ctest -D NightlyMemCheck

NightlyMemCheck: testing/CMakeFiles/NightlyMemCheck
NightlyMemCheck: testing/CMakeFiles/NightlyMemCheck.dir/build.make
.PHONY : NightlyMemCheck

# Rule to build all files generated by this target.
testing/CMakeFiles/NightlyMemCheck.dir/build: NightlyMemCheck
.PHONY : testing/CMakeFiles/NightlyMemCheck.dir/build

testing/CMakeFiles/NightlyMemCheck.dir/clean:
	cd /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing && $(CMAKE_COMMAND) -P CMakeFiles/NightlyMemCheck.dir/cmake_clean.cmake
.PHONY : testing/CMakeFiles/NightlyMemCheck.dir/clean

testing/CMakeFiles/NightlyMemCheck.dir/depend:
	cd /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing/CMakeFiles/NightlyMemCheck.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : testing/CMakeFiles/NightlyMemCheck.dir/depend

