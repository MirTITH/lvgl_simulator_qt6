cmake_minimum_required(VERSION 3.14)

project(freetype)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.c)

add_library(freetype STATIC ${SOURCES})
add_library(freetype::freetype ALIAS freetype)

target_include_directories(freetype PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src/base
    ${CMAKE_CURRENT_LIST_DIR}/src/base/include
    ${CMAKE_CURRENT_LIST_DIR}/src/cache/include
    ${CMAKE_CURRENT_LIST_DIR}/src/gzip/include
    ${CMAKE_CURRENT_LIST_DIR}/src/sfnt/include
    ${CMAKE_CURRENT_LIST_DIR}/src/smooth/include
    ${CMAKE_CURRENT_LIST_DIR}/src/truetype/include
)

target_compile_definitions(freetype PUBLIC
    FT2_BUILD_LIBRARY
    FT_CONFIG_MODULES_H="../lvgl/src/libs/freetype/ftmodule.h"
    FT_CONFIG_OPTIONS_H="../lvgl/src/libs/freetype/ftoption.h"
)

target_link_libraries(freetype PUBLIC
    lvgl::lvgl
)
