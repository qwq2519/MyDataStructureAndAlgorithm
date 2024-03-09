cmake_minimum_required(VERSION 3.26)
project(MyDataStructureAndAlgorithm CXX)

set(CMAKE_CXX_STANDARD 20)

# 添加头文件目录
include_directories(${CMAKE_SOURCE_DIR}/Src)


# 添加源文件

add_executable(MyDataStructureAndAlgorithm
        TestDemo/MyStackTest.cpp
)

