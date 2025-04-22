cmake_minimum_required(VERSION 3.10)
project(RendererLib)

set(CMAKE_BUILD_TYPE Release)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Image/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Object/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/*.cpp
)

file(GLOB_RECURSE HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Linalg.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Image/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Object/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Renderer/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Scene/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../renderer_include.h
)

add_library(Renderer STATIC ${SOURCES} ${HEADERS})

# Указываем путь до Eigen
target_include_directories(Renderer
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/eigen
        ${CMAKE_CURRENT_SOURCE_DIR}
)