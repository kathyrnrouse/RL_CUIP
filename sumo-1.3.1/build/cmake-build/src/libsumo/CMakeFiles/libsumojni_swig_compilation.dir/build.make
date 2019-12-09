# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build

# Utility rule file for libsumojni_swig_compilation.

# Include the progress variables for this target.
include src/libsumo/CMakeFiles/libsumojni_swig_compilation.dir/progress.make

src/libsumo/CMakeFiles/libsumojni_swig_compilation: src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp


src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/Edge.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/Helper.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/InductionLoop.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/Junction.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/Lane.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/LaneArea.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/MultiEntryExit.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/POI.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/Person.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/Polygon.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/Route.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/Simulation.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/Subscription.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/TraCIConstants.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/TraCIDefs.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/TrafficLight.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/Vehicle.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/VehicleType.h
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/libsumo.i
src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp: ../../src/libsumo/libsumo.i
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Swig compile libsumo.i for java"
	cd /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build/src/libsumo && /usr/local/Cellar/cmake/3.15.3/bin/cmake -E make_directory /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build/src/libsumo/java /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build/src/libsumo/java
	cd /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build/src/libsumo && /usr/local/Cellar/cmake/3.15.3/bin/cmake -E touch /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build/src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp
	cd /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build/src/libsumo && /usr/local/Cellar/cmake/3.15.3/bin/cmake -E env SWIG_LIB=/usr/local/Cellar/swig/4.0.1/share/swig/4.0.1 /usr/local/bin/swig -java -package org.eclipse.sumo.libsumo -outdir /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build/src/libsumo/java -c++ -I/opt/X11/include -I/usr/local/include -I/usr/X11R6/include -I/Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build/src -I/Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/src -I/Library/Developer/CommandLineTools/SDKs/MacOSX10.14.sdk/System/Library/Frameworks/JavaVM.framework/Headers -o /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build/src/libsumo/java/libsumoJAVA_wrap.cxx /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/src/libsumo/libsumo.i

libsumojni_swig_compilation: src/libsumo/CMakeFiles/libsumojni_swig_compilation
libsumojni_swig_compilation: src/libsumo/CMakeFiles/libsumojni.dir/libsumoJAVA.stamp
libsumojni_swig_compilation: src/libsumo/CMakeFiles/libsumojni_swig_compilation.dir/build.make

.PHONY : libsumojni_swig_compilation

# Rule to build all files generated by this target.
src/libsumo/CMakeFiles/libsumojni_swig_compilation.dir/build: libsumojni_swig_compilation

.PHONY : src/libsumo/CMakeFiles/libsumojni_swig_compilation.dir/build

src/libsumo/CMakeFiles/libsumojni_swig_compilation.dir/clean:
	cd /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build/src/libsumo && $(CMAKE_COMMAND) -P CMakeFiles/libsumojni_swig_compilation.dir/cmake_clean.cmake
.PHONY : src/libsumo/CMakeFiles/libsumojni_swig_compilation.dir/clean

src/libsumo/CMakeFiles/libsumojni_swig_compilation.dir/depend:
	cd /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1 /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/src/libsumo /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build/src/libsumo /Users/krouse/Documents/CUIP/deepq_example/sumo-1.3.1/build/cmake-build/src/libsumo/CMakeFiles/libsumojni_swig_compilation.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/libsumo/CMakeFiles/libsumojni_swig_compilation.dir/depend
