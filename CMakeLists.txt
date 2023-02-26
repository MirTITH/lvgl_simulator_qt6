cmake_minimum_required(VERSION 3.16)

project(lvgl_simulator_qt6 VERSION 1.0.0)

add_subdirectory(lvgl)

set(CMAKE_AUTOMOC ON) # 设置自动生成moc文件,AUTOMOC打开可以省去QT5_WRAP_CPP命令
set(CMAKE_AUTOUIC ON) # 设置自动生成ui.h文件,AUTOUIC打开可以省去QT5_WRAP_UI命令
set(CMAKE_AUTORCC ON) # 【optional】设置自动处理.qrc文件

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick REQUIRED)

#qt_standard_project_setup()

file(GLOB_RECURSE SOURCES
    src/*.cpp src/*.c
)

add_executable(${PROJECT_NAME}
    qml.qrc
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ./src
    ./lvgl
)

#qt_add_qml_module(${PROJECT_NAME}
#    URI LCD VERSION 1.0
#)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Quick
    lvgl::lvgl
    lvgl::demos
)

# 添加这行使得 Qt Creator 可以对Cpp中的Qml组件自动提示
#set(QML_IMPORT_PATH ${CMAKE_CURRENT_BINARY_DIR}/LCD CACHE STRING "qml import path" FORCE)

# cmake_minimum_required(VERSION 3.16)

# project(lvgl_simulator_qt6 VERSION 0.1 LANGUAGES CXX)

# set(CMAKE_AUTOMOC ON)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

# qt_add_executable(${PROJECT_NAME}
#     src/main.cpp
#     src/lcd.cpp
# )

# target_include_directories(applvgl_simulator_qt6 PRIVATE
#     ./include
# )

# qt_add_qml_module(applvgl_simulator_qt6
#     URI lvgl_simulator_qt6
#     VERSION 1.0
#     QML_FILES
#     qml/main.qml
# )

# set_target_properties(applvgl_simulator_qt6 PROPERTIES
#     MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# target_link_libraries(applvgl_simulator_qt6
#     PRIVATE Qt6::Quick)

# install(TARGETS applvgl_simulator_qt6
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
