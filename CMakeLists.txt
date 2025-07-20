cmake_minimum_required(VERSION 3.31)
project(AStarGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(AStarGame main.cpp
        GlobalMap.cpp
        GlobalMap.h
        SearchState.cpp
        SearchState.h
        Observer.h
        Subject.h
        Display.h)
