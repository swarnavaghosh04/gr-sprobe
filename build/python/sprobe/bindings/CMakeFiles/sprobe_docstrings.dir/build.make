# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_SOURCE_DIR = /home/swarnava/devel/gr-sprobe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/swarnava/devel/gr-sprobe/build

# Utility rule file for sprobe_docstrings.

# Include any custom commands dependencies for this target.
include python/sprobe/bindings/CMakeFiles/sprobe_docstrings.dir/compiler_depend.make

# Include the progress variables for this target.
include python/sprobe/bindings/CMakeFiles/sprobe_docstrings.dir/progress.make

python/sprobe/bindings/CMakeFiles/sprobe_docstrings: python/sprobe/bindings/docstring_status

python/sprobe/bindings/docstring_status:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/swarnava/devel/gr-sprobe/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Adding docstrings into sprobe pybind headers ..."
	cd /home/swarnava/devel/gr-sprobe/build/python/sprobe/bindings && /usr/bin/python3 /home/swarnava/devel/gr-sprobe/docs/doxygen/update_pydoc.py sub --json_path /home/swarnava/devel/gr-sprobe/build/python/sprobe/bindings/extracted_docstrings.json --bindings_dir /home/swarnava/devel/gr-sprobe/python/sprobe/bindings/docstrings --output_dir /home/swarnava/devel/gr-sprobe/build/python/sprobe/bindings --filter gr::sprobe

python/sprobe/bindings/CMakeFiles/sprobe_docstrings.dir/codegen:
.PHONY : python/sprobe/bindings/CMakeFiles/sprobe_docstrings.dir/codegen

sprobe_docstrings: python/sprobe/bindings/CMakeFiles/sprobe_docstrings
sprobe_docstrings: python/sprobe/bindings/docstring_status
sprobe_docstrings: python/sprobe/bindings/CMakeFiles/sprobe_docstrings.dir/build.make
.PHONY : sprobe_docstrings

# Rule to build all files generated by this target.
python/sprobe/bindings/CMakeFiles/sprobe_docstrings.dir/build: sprobe_docstrings
.PHONY : python/sprobe/bindings/CMakeFiles/sprobe_docstrings.dir/build

python/sprobe/bindings/CMakeFiles/sprobe_docstrings.dir/clean:
	cd /home/swarnava/devel/gr-sprobe/build/python/sprobe/bindings && $(CMAKE_COMMAND) -P CMakeFiles/sprobe_docstrings.dir/cmake_clean.cmake
.PHONY : python/sprobe/bindings/CMakeFiles/sprobe_docstrings.dir/clean

python/sprobe/bindings/CMakeFiles/sprobe_docstrings.dir/depend:
	cd /home/swarnava/devel/gr-sprobe/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/swarnava/devel/gr-sprobe /home/swarnava/devel/gr-sprobe/python/sprobe/bindings /home/swarnava/devel/gr-sprobe/build /home/swarnava/devel/gr-sprobe/build/python/sprobe/bindings /home/swarnava/devel/gr-sprobe/build/python/sprobe/bindings/CMakeFiles/sprobe_docstrings.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : python/sprobe/bindings/CMakeFiles/sprobe_docstrings.dir/depend

