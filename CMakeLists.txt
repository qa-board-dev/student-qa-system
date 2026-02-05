cmake_minimum_required(VERSION 3.31)
-DCMAKE_TOOLCHAIN_FILE=/absolute/path/to/your/repo/vcpkg/scripts/buildsystems/vcpkg.cmake

project(CSE360)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion")

add_executable(CSE360 main.cpp)


