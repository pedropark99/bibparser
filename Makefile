# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_SOURCE_DIR = /c/Users/pedro.duarte/Documents/projects/bibparser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /c/Users/pedro.duarte/Documents/projects/bibparser

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake.exe -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake.exe --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /c/Users/pedro.duarte/Documents/projects/bibparser/CMakeFiles /c/Users/pedro.duarte/Documents/projects/bibparser//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /c/Users/pedro.duarte/Documents/projects/bibparser/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named bibparser

# Build rule for target.
bibparser: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 bibparser
.PHONY : bibparser

# fast build rule for target.
bibparser/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/build
.PHONY : bibparser/fast

src/global_variables.o: src/global_variables.cpp.o
.PHONY : src/global_variables.o

# target to build an object file
src/global_variables.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/global_variables.cpp.o
.PHONY : src/global_variables.cpp.o

src/global_variables.i: src/global_variables.cpp.i
.PHONY : src/global_variables.i

# target to preprocess a source file
src/global_variables.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/global_variables.cpp.i
.PHONY : src/global_variables.cpp.i

src/global_variables.s: src/global_variables.cpp.s
.PHONY : src/global_variables.s

# target to generate assembly for a file
src/global_variables.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/global_variables.cpp.s
.PHONY : src/global_variables.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/read_bib.o: src/read_bib.cpp.o
.PHONY : src/read_bib.o

# target to build an object file
src/read_bib.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/read_bib.cpp.o
.PHONY : src/read_bib.cpp.o

src/read_bib.i: src/read_bib.cpp.i
.PHONY : src/read_bib.i

# target to preprocess a source file
src/read_bib.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/read_bib.cpp.i
.PHONY : src/read_bib.cpp.i

src/read_bib.s: src/read_bib.cpp.s
.PHONY : src/read_bib.s

# target to generate assembly for a file
src/read_bib.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/read_bib.cpp.s
.PHONY : src/read_bib.cpp.s

src/string_utils.o: src/string_utils.cpp.o
.PHONY : src/string_utils.o

# target to build an object file
src/string_utils.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/string_utils.cpp.o
.PHONY : src/string_utils.cpp.o

src/string_utils.i: src/string_utils.cpp.i
.PHONY : src/string_utils.i

# target to preprocess a source file
src/string_utils.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/string_utils.cpp.i
.PHONY : src/string_utils.cpp.i

src/string_utils.s: src/string_utils.cpp.s
.PHONY : src/string_utils.s

# target to generate assembly for a file
src/string_utils.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/string_utils.cpp.s
.PHONY : src/string_utils.cpp.s

src/tokenizer.o: src/tokenizer.cpp.o
.PHONY : src/tokenizer.o

# target to build an object file
src/tokenizer.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/tokenizer.cpp.o
.PHONY : src/tokenizer.cpp.o

src/tokenizer.i: src/tokenizer.cpp.i
.PHONY : src/tokenizer.i

# target to preprocess a source file
src/tokenizer.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/tokenizer.cpp.i
.PHONY : src/tokenizer.cpp.i

src/tokenizer.s: src/tokenizer.cpp.s
.PHONY : src/tokenizer.s

# target to generate assembly for a file
src/tokenizer.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/bibparser.dir/build.make CMakeFiles/bibparser.dir/src/tokenizer.cpp.s
.PHONY : src/tokenizer.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... bibparser"
	@echo "... src/global_variables.o"
	@echo "... src/global_variables.i"
	@echo "... src/global_variables.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/read_bib.o"
	@echo "... src/read_bib.i"
	@echo "... src/read_bib.s"
	@echo "... src/string_utils.o"
	@echo "... src/string_utils.i"
	@echo "... src/string_utils.s"
	@echo "... src/tokenizer.o"
	@echo "... src/tokenizer.i"
	@echo "... src/tokenizer.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

