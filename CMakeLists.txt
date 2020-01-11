cmake_minimum_required(VERSION 3.13)
project(ex2)

set(CMAKE_CXX_STANDARD 14)


add_executable(ex2 main.cpp SearchTree.h AVLTree.h generic_node.h StatusType.h
        RankTree.h UnionFind.h HashTable.h HashTable.cpp DataCenter.cpp DataCenter.h
        DataCenterManager.cpp DataCenterManager.h)



