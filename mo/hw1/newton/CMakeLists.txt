cmake_minimum_required(VERSION 3.0)

project(newton_method VERSION 1.0 LANGUAGES C CXX)

set(release_flags
    "-O3 -march=native -g -Wall -ftemplate-depth=10000 -std=c++17"
)

set(compile_flags "-fsanitize=address -fsanitize=leak -fsanitize=undefined \
-fdiagnostics-color=always -fdiagnostics-generate-patch \
-g -Wall -ftemplate-depth=10000 -std=c++17"
)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${compile_flags}")
message("CMAKE_CXX_FLAGS" ${CMAKE_CXX_FLAGS})

add_executable(test
    test.cpp 
    utils_v_double.cpp
    solve_system.cpp
    holetskiy.cpp
    newton.cpp
)

