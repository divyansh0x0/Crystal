cmake_minimum_required(VERSION 3.5.0)
project(Crystal-Test VERSION 0.1.0 LANGUAGES C CXX)
cmake_minimum_required(VERSION 3.5.0)

set(ALL_TEST_FILES "matrix.h" "vector.h")
set(GTEST_COLOR ON)
include(CTest)

#########################
#fetch external libraries
#########################
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
    GIT_PROGRESS ON
)
FetchContent_MakeAvailable(googletest)

#prevent overriding the parent project's compiler/linker settings on windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


#########################
#build tests
#########################
include(GoogleTest)
add_executable(Crystal-Test "tests.cpp" ${ALL_TEST_FILES})
target_link_libraries(Crystal-Test PRIVATE crystal GTest::gtest_main)

gtest_discover_tests(Crystal-Test)


