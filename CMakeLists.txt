cmake_minimum_required(VERSION 3.26)
project(MyDataStructureAndAlgorithm CXX)

set(CMAKE_CXX_STANDARD 20)

# 添加头文件目录
include_directories(${CMAKE_SOURCE_DIR}/Src/ds)
include_directories(${CMAKE_SOURCE_DIR}/Src/alg)




# 添加源文件
add_executable(MyDataStructureAndAlgorithm
        ./Src/alg/TopologicalSort.cpp
        #TestDemo/MyStackTest.cpp
        #TestDemo/MyQueueTest.cpp
        #TestDemo/MyLinkedListTest.cpp
        #TestDemo/Test.cpp
        #TestDemo/MyVectorTest.cpp
        #TestDemo/MyLinkedListTest.cpp
)
