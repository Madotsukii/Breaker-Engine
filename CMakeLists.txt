cmake_minimum_required(VERSION 2.6)
project(BreakerEngine)

# The version number.
set(BreakerEngine_VERSION_MAJOR 0)
set(BreakerEngine_VERSION_MINOR 1)

# Compiler instructions
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libc++")
set(CMAKE_CXX_LINK_FLAGS "-lc++abi")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
 
# Configure a header file to pass some of the CMake settings
# to the source code
configure_file(
	"${PROJECT_SOURCE_DIR}/src/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)
 
# Add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")
 
# Add the executable
add_executable(BreakerEngine src/main.cpp)

#Add the install targets
install(TARGETS BreakerEngine DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.h" DESTINATION include)
