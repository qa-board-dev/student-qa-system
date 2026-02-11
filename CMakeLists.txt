cmake_minimum_required(VERSION 3.31)
project(Project_A1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Project_A1 main.cpp
        mainwindow.h
        mainwindow.cpp
)
target_link_libraries(Project_A1 PRIVATE Qt6::Widgets)
