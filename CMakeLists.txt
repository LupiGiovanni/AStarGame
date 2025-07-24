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
        GameCharacter.cpp
        GameCharacter.h
        MapView.cpp
        MapView.h
        GameManager.cpp
        GameManager.h)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(SFMLprova main.cpp)

target_link_libraries(SFMLprova sfml-graphics sfml-window sfml-system)
