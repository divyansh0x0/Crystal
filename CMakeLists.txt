cmake_minimum_required(VERSION 3.31.0)
project(crystal VERSION 0.1.0 LANGUAGES C CXX)

# ########################
# fetch external libraries
# ########################
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
    GIT_PROGRESS ON
)
FetchContent_MakeAvailable(googletest)

# prevent overriding the parent project's compiler/linker settings on windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ##############################
# Setting up build options
# #############################

# Do some build optimization and checking
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/out")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/out/lib")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Og")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -Og")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

# msvc hot reload
if(MSVC)
    add_compile_options("/ZI")
    add_link_options("/INCREMENTAL")
endif()

# ################################################
# Subdirectories
# ################################################
message("Building crystal with build type: ${CMAKE_BUILD_TYPE}")

enable_testing()
include(CTest)

add_subdirectory(crystal)
add_subdirectory(tests)


