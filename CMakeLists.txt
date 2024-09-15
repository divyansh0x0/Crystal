cmake_minimum_required(VERSION 3.5.0)
project(Crystal VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/out")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/out/lib")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_subdirectory(crystal)

add_executable(Quartz test.cpp)

include_directories(crystal/include)


target_link_libraries(Quartz crystal)


#Need compile_commands.json in root folder so that clangd can pick it up
# Copy to source directory
add_custom_target(
    copy-compile-commands ALL
    DEPENDS
        ${CMAKE_CURRENT_LIST_DIR}/compile_commands.json
    )
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_LIST_DIR}/compile_commands.json
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_LIST_DIR}/compile_commands.json
    DEPENDS
        # Unlike "proper" targets like executables and libraries, 
        # custom command / target pairs will not set up source
        # file dependencies, so we need to list file explicitly here
        generate-compile-commands
        ${CMAKE_BINARY_DIR}/compile_commands.json
    )

# Generate the compilation commands. Necessary so cmake knows where it came
# from and if for some reason you delete it.
add_custom_target(generate-compile-commands
    DEPENDS
        ${CMAKE_BINARY_DIR}/compile_commands.json
    )
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/compile_commands.json
    COMMAND ${CMAKE_COMMAND} -B${CMAKE_BINARY_DIR} -S${CMAKE_SOURCE_DIR}
    )



