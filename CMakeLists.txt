cmake_minimum_required(VERSION 3.23)
project(ece-city-2-c C)

set(CMAKE_C_STANDARD 99)

# ajouter raylib au projet CMake
add_subdirectory(raylib)

add_executable(ece-city-2-c main.c test.c test.h)
# linker statiquement raylib au projet
target_link_libraries(ece-city-2-c raylib)


