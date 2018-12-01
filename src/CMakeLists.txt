cmake_minimum_required(VERSION 3.7)
project(Bulbasaur)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


set(TARGET bulbasaur)

# Find the library
find_package(PkgConfig REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(DtkWidget REQUIRED)

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE FORMS "*.ui")
file(GLOB_RECURSE RESOURCES "*.qrc")
add_executable(${TARGET} ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})

target_include_directories(${TARGET} PUBLIC
        ${DtkWidget_INCLUDE_DIRS}
        ${Qt5Concurrent_INCLUDE_DIRS}
        )
target_link_libraries(${TARGET}
        ${DtkWidget_LIBRARIES}
        ${Qt5Widgets_LIBRARIES}
        ${Qt5Concurrent_LIBRARIES}
        )