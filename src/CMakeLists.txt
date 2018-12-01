cmake_minimum_required(VERSION 3.7)
project(Bulbasaur)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
if (NOT (${CMAKE_BUILD_TYPE} MATCHES "Debug"))
    set(CMAKE_CXX_FLAGS -O3)
    # generate qm files
    execute_process(COMMAND bash "translate_generation.sh"
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src)
else ()
    set(CMAKE_CXX_COMPILER "clang++")
endif ()

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


#准备的版本设置

set(_VERSION_MAJOR 1)
set(_VERSION_MINOR 0)
set(_VERSION_PATCH 0)

#说明要生成的是deb包

set(CPACK_GENERATOR "DEB")

############下面是设置debian/control文件中的内容

#设置版本信息
set(CPACK_PACKAGE_VERSION_MAJOR "${_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${_VERSION_PATCH}")

#设置安装包的包名，打好的包将会是packagename-version-linux.deb，如果不设置，默认是工程名
set(CPACK_PACKAGE_NAME "cn.net.pikachu.bulbasaur")

#设置程序名，就是程序安装后的名字
set(CPACK_DEBIAN_PACKAGE_NAME "bulbasaur")

#设置架构
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")

#设置依赖
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libdtkwidget-dev")

#设置section
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")

#设置priority
set(CPACK_DEBIAN_PACKAGE_PRIORITY "Optional")

#设置description
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "TreeSize for Deepin, Quickly Scan Directory Sizes and Find Space Hogs.")

#设置联系方式
set(CPACK_PACKAGE_CONTACT "pikachuhy@163.com")

#设置维护人
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "PikachuHy")
set(CMAKE_INSTALL_PREFIX /usr)
install(TARGETS ${TARGET} DESTINATION bin)
install(FILES ../${TARGET}.desktop DESTINATION share/applications)
install(FILES ../${TARGET}.png DESTINATION share/icons)
# Install qm files
file(GLOB QM_FILES "translations/*.qm")
install(FILES ${QM_FILES} DESTINATION share/${TARGET}/translations)
include(CPack)