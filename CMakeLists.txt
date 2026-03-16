cmake_minimum_required(VERSION 4.1)
project(LinkedList)

add_executable(LinkedList main.cpp
        LinkedLists.hpp)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER clang++)

set(COMMON_FLAGS
        -std=c++23
        -O0
#        -mrdseed
#        -mrdrnd
#        -march=native
        -m64
        -fansi-escape-codes
        -fcolor-diagnostics
        -fdiagnostics-show-option
        -fcxx-exceptions
        -fexceptions
        -fcxx-exceptions
        -Wall
        -flto
        #        -v
        -Wno-deprecated-declarations
)

target_compile_options(LinkedList PRIVATE
        ${COMMON_FLAGS}
)

target_link_libraries(LinkedList PRIVATE fmt)

set_target_properties(LinkedList PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)