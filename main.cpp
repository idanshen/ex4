#include <iostream>
#include "UnionFind.h"

int main() {
    auto tmp = UnionFind<int>(10);
    auto ptr = new int*;
    tmp.Find(2, ptr);
    **ptr = 5;
    tmp.Find(3, ptr);
    **ptr = 2;
    tmp.Union(1,2);
    tmp.Union(2,3);
    auto ptr2 = new int*;
    tmp.Find(1, ptr2);
    return 0;
}