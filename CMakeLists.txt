cmake_minimum_required(VERSION 3.15)
project(funny-chicken-engine)

include_directories(include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_C_FLAGS "-Wall -include /usr/include/my_std.h")

set(SOURCE src/main.c
        src/glfw_callback.c
        src/opengl_engine.c
        src/opengl_context.c
        src/global_variable.c
)

set(BIN funny)

add_executable(${BIN} ${SOURCE})
if(DEBUG)
        target_compile_definitions(${BIN} PUBLIC DEBUG)
        set(CMAKE_C_FLAGS "-Wall -g -include /usr/include/my_std.h")
endif()

target_link_libraries(${BIN} my_std glfw glad)
