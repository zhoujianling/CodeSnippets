cmake_minimum_required(VERSION 3.5) #设置CMake最小版本
project (dll_test_library) #设置工程名

set (
    SRC_FILES
    Library.cpp
)
add_library(DllTestLibrary SHARED ${SRC_FILES}) #生成动态库

target_include_directories(DllTestLibrary PUBLIC include)
set(CXX_STANDARD 17)