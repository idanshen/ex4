cmake_minimum_required(VERSION 3.13)
project(ex2)

set(CMAKE_CXX_STANDARD 14)


add_executable(ex2 main_test.cpp SearchTree.h AVLTree.h generic_node.h
        RankTree.h UnionFind.h HashTable.h HashTable.cpp ServerData.cpp ServerData.h
        DataCenterManager.cpp DataCenterManager.h library2.h library2.cpp)



