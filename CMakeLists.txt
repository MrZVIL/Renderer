cmake_minimum_required(VERSION 3.10)
project(RendererRoot)

set(CMAKE_BUILD_TYPE Release)

add_subdirectory(src)
add_subdirectory(Tests)
add_subdirectory(InteractiveApp)
