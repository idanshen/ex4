#include <iostream>
#include "RankTree.h"

int main() {
    auto tmp_tree = RankTree<int>();
    auto n1 = new int(2);
    tmp_tree.insert(*n1);
    auto n2 = new int(3);
    tmp_tree.insert(*n2);
    auto n3 = new int(4);
    tmp_tree.insert(*n3);
    auto n4 = new int(5);
    tmp_tree.insert(*n4);
    //tmp_tree.remove(3);
    auto n5 = new int(6);
    tmp_tree.insert(*n5);
    auto sum = new int;
    tmp_tree.SumHighest(5, sum);
    printf("hello world");
    return 0;
}