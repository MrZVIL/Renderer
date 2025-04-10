project(test)

include_directories(external/eigen)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

set(CMAKE_CXX_FLAGS "-std=c++20 -O3 -Wall")

set(SRC_LIST src/Image/Color.cpp src/Image/Image.cpp src/Image/BMPWriter.cpp src/Object/Triangle.cpp 
    src/Object/Object.cpp src/Scene/Camera.cpp src/Scene/World.cpp src/Renderer/Renderer.cpp test.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external)

target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
