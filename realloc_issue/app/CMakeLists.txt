cmake_minimum_required(VERSION 3.16)

project(app)

set(CMAKE_CXX_STANDARD 20)

add_executable(
    app
    main.cpp
    )

target_link_libraries(
    app
    iwasm
)