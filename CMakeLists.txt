cmake_minimum_required(VERSION 3.25)
project(Lab02)

set(CMAKE_CXX_STANDARD 20)
set(SDL2_INCLUDE_DIR C:/Users/mario/SDL/SDL2-2.28.1/include)
set(SDL2_LIB_DIR C:/Users/mario/SDL/SDL2-2.28.1/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(Lab02 main.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)