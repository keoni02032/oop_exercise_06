cmake_minimum_required(VERSION 3.1)

project(lab6)

add_executable(lab6
    main.cpp)

set_property(TARGET lab6 PROPERTY CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -Wall -Wextra")
