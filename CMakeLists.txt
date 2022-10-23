cmake_minimum_required (VERSION 3.8)

project ("richman")

set(CMAKE_CXX_STANDARD 11)

# 将源代码添加到此项目的可执行文件。
add_executable (richman "main.cpp" )
add_subdirectory (src)


include_directories(${PROJECT_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} PUBLIC src)

