cmake_minimum_required(VERSION 3.5)
project(test)

include_directories(external/CImg)
include_directories(external/eigen)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

set(CMAKE_CXX_FLAGS "-std=c++20 -Wall")

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})


set(SRC_LIST src/Image/PrimitiveColor.cpp src/Image/Color.cpp src/Image/Image.cpp src/Object/Point.cpp src/Object/Triangle.cpp test.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
