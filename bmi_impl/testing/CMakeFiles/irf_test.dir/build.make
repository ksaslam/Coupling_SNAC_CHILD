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

# Include any dependencies generated for this target.
include testing/CMakeFiles/irf_test.dir/depend.make

# Include the progress variables for this target.
include testing/CMakeFiles/irf_test.dir/progress.make

# Include the compile flags for this target's objects.
include testing/CMakeFiles/irf_test.dir/flags.make

testing/CMakeFiles/irf_test.dir/irf_test.c.o: testing/CMakeFiles/irf_test.dir/flags.make
testing/CMakeFiles/irf_test.dir/irf_test.c.o: testing/irf_test.c
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object testing/CMakeFiles/irf_test.dir/irf_test.c.o"
	cd /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing && /opt/local/bin/mpicc-mpich-mp  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/irf_test.dir/irf_test.c.o   -c /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing/irf_test.c

testing/CMakeFiles/irf_test.dir/irf_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/irf_test.dir/irf_test.c.i"
	cd /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing && /opt/local/bin/mpicc-mpich-mp  $(C_DEFINES) $(C_FLAGS) -E /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing/irf_test.c > CMakeFiles/irf_test.dir/irf_test.c.i

testing/CMakeFiles/irf_test.dir/irf_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/irf_test.dir/irf_test.c.s"
	cd /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing && /opt/local/bin/mpicc-mpich-mp  $(C_DEFINES) $(C_FLAGS) -S /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing/irf_test.c -o CMakeFiles/irf_test.dir/irf_test.c.s

testing/CMakeFiles/irf_test.dir/irf_test.c.o.requires:
.PHONY : testing/CMakeFiles/irf_test.dir/irf_test.c.o.requires

testing/CMakeFiles/irf_test.dir/irf_test.c.o.provides: testing/CMakeFiles/irf_test.dir/irf_test.c.o.requires
	$(MAKE) -f testing/CMakeFiles/irf_test.dir/build.make testing/CMakeFiles/irf_test.dir/irf_test.c.o.provides.build
.PHONY : testing/CMakeFiles/irf_test.dir/irf_test.c.o.provides

testing/CMakeFiles/irf_test.dir/irf_test.c.o.provides.build: testing/CMakeFiles/irf_test.dir/irf_test.c.o

# Object files for target irf_test
irf_test_OBJECTS = \
"CMakeFiles/irf_test.dir/irf_test.c.o"

# External object files for target irf_test
irf_test_EXTERNAL_OBJECTS =

testing/irf_test: testing/CMakeFiles/irf_test.dir/irf_test.c.o
testing/irf_test: testing/CMakeFiles/irf_test.dir/build.make
testing/irf_test: bmi/libbmi.dylib
testing/irf_test: testing/CMakeFiles/irf_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable irf_test"
	cd /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/irf_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
testing/CMakeFiles/irf_test.dir/build: testing/irf_test
.PHONY : testing/CMakeFiles/irf_test.dir/build

testing/CMakeFiles/irf_test.dir/requires: testing/CMakeFiles/irf_test.dir/irf_test.c.o.requires
.PHONY : testing/CMakeFiles/irf_test.dir/requires

testing/CMakeFiles/irf_test.dir/clean:
	cd /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing && $(CMAKE_COMMAND) -P CMakeFiles/irf_test.dir/cmake_clean.cmake
.PHONY : testing/CMakeFiles/irf_test.dir/clean

testing/CMakeFiles/irf_test.dir/depend:
	cd /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing /Users/eunseo/projects/Coupling_SNAC_CHILD/bmi_impl/testing/CMakeFiles/irf_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : testing/CMakeFiles/irf_test.dir/depend
