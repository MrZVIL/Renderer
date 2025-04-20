cmake_minimum_required(VERSION 3.10)
project(test)



set(CMAKE_BUILD_TYPE Release)

set(SRC_LIST test3.cpp)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} PRIVATE Renderer)
