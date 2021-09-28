cmake_minimum_required(VERSION 3.5) #设置CMake最小版本
project (dll_test) #设置工程名

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output)
set (
    SRC_FILES
    Main.cpp
)
add_executable(DllTest ${SRC_FILES}) #生成可执行文件


add_subdirectory(Library)
target_link_libraries(DllTest PRIVATE DllTestLibrary)

set(CXX_STANDARD 17)