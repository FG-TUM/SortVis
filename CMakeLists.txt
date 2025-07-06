cmake_minimum_required(VERSION 3.31)
project(SortVis)

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

file(GLOB_RECURSE SOURCES
     src/sortvis/*.cpp
     src/sortvis/*.h
)

set(EXE_NAME SortVis)

add_executable(${EXE_NAME} ${SOURCES})

target_link_libraries(${EXE_NAME}
        PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

target_include_directories(${EXE_NAME}
        PRIVATE
        src/
)

