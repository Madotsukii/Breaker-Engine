# Minimum required CMake version
cmake_minimum_required(VERSION 2.6)

# Project name
project(BreakerEngine)

# The version number
set(BreakerEngine_VERSION_MAJOR 0)
set(BreakerEngine_VERSION_MINOR 2)

# Compiler instructions
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libc++")
set(CMAKE_CXX_LINK_FLAGS "-lc++abi -lpthread")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Configure a header file to pass some of the CMake settings
# to the source code
configure_file(
	"${PROJECT_SOURCE_DIR}/src/config.hpp.in"
	"${PROJECT_BINARY_DIR}/config.hpp"
)

# Add the binary tree to the search path for include files
# so that we will find config.h
include_directories("${PROJECT_BINARY_DIR}")

# Add the executable
add_executable(
	BreakerEngine
	src/main.cpp
	src/core/thread.cpp
	src/core/io/directory.cpp
	src/core/io/file.cpp
	src/core/logging/log.cpp
)

#Add the install targets
install(TARGETS BreakerEngine DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/config.hpp" DESTINATION include)
