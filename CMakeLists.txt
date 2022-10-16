# CMakeList.txt: cpp-cmake 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("richman")

# 将源代码添加到此项目的可执行文件。
add_executable (richman "main.cpp" )
add_subdirectory (src)

include_directories(${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} PUBLIC src)

# TODO: 如有需要，请添加测试并安装目标。
option(BUILD_TEST "Whether or not to build the tests" ON)
if (${BUILD_TEST})
    message(STATUS "Building tests")
    enable_testing()  # Enable testing only works in root scope
    add_subdirectory(tests)
endif ()
