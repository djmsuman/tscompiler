cmake_minimum_required(VERSION 3.30)

# Project name
project(TypeScriptCompiler VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add header files
file(GLOB_RECURSE HEADERS "src/*.h" "include/*.h")

# Include directories
include_directories(include src)

# Create the executable
add_executable(tscompiler ${SOURCES} ${HEADERS})

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Platform-specific configurations
if(APPLE)
    # macOS-specific settings
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version")

    # Enable universal binary for macOS (AMD64 + ARM64)
    set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "Build architectures for macOS" FORCE)
elseif(UNIX AND NOT APPLE)
    # Linux-specific settings
    # Note: For ARM64 on Linux, you typically cross-compile or use a native ARM64 system
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
        # ARM64-specific flags for Linux
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8-a")
    else()
        # AMD64-specific flags for Linux
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64")
    endif()
elseif(WIN32)
    # Windows-specific settings
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "ARM64")
        # ARM64-specific flags for Windows
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:ARM64")
    else()
        # AMD64-specific flags for Windows
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2")
    endif()
endif()

# Add compiler warnings
if(MSVC)
    target_compile_options(tscompiler PRIVATE /W4 /WX)
else()
    target_compile_options(tscompiler PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# Install target
install(TARGETS tscompiler DESTINATION bin)

# Enable testing
enable_testing()

# Add a simple test
add_test(NAME RunCompiler COMMAND tscompiler)
