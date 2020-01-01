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
    generic_node<K>(K* data) : data(data), height(0), left_son(NULL), right_son(NULL), father(NULL){ };
    generic_node<K>() : height(0), left_son(NULL), right_son(NULL), father(NULL) {data= nullptr;}
    ~generic_node() {
        delete(data);
    };
};

#endif //EX2_GENERIC_NODE_H
