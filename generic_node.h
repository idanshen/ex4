#ifndef EX2_GENERIC_NODE_H
#define EX2_GENERIC_NODE_H

#include <cstdlib>

template <class K>
class generic_node {
public:
    K *data;
    int height;
    struct generic_node *left_son;
    struct generic_node *right_son;
    struct generic_node *father;
    int subtree_size;
    int subtree_sum;
    generic_node<K>(K* data) : data(data), height(0), left_son(NULL), right_son(NULL), father(NULL), subtree_size(1){
        if(!data){
            this->data=new K();
            subtree_sum=0;

        }
        else {
            subtree_sum = 0 + *data;
        }
    };
    generic_node<K>() : height(0), left_son(NULL), right_son(NULL), father(NULL), subtree_size(1), subtree_sum(0) {data= nullptr;}
    ~generic_node() {
        delete data;
    };
};

#endif //EX2_GENERIC_NODE_H
