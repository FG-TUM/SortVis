cmake_minimum_required(VERSION 3.31)
project(SortingVisualizer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "SortVis")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

file(GLOB_RECURSE WIDGET_SOURCES
     src/sortvis/*.cpp
     src/sortvis/*.h
)

add_executable(SortingVisualizer src/sortvis/main.cpp ${WIDGET_SOURCES})

target_link_libraries(SortingVisualizer
        PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

target_include_directories(SortingVisualizer
        PRIVATE
        src/
)

