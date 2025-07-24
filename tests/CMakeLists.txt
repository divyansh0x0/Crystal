cmake_minimum_required(VERSION 3.31.0)
project(crystal_tests VERSION 0.1.0 LANGUAGES C CXX)

set(ALL_TEST_FILES matrix.h vector.h)
set(GTEST_COLOR ON)


#########################
#build tests
#########################

include(GoogleTest)
# define a function that can be used to add tests automatically
function (create_test name)
    # each test creates its own executable
    add_executable(${name} ${name}.cpp)
    message("Test executable for " ${name} ".cpp built successfully")
    # we need to link each test separately against google test
    target_link_libraries(${name} crystal GTest::gtest_main)

    # register the test with CTest, so we execute it automatically when running CTest later
    add_test(NAME ${name} COMMAND $<TARGET_FILE:${name}>)
    # gtest_discover_tests(${name})
endfunction()

create_test(matrix)
create_test(vector)
create_test(gui)
