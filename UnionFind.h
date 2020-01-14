#ifndef EX2_UNIONFIND_H
#define EX2_UNIONFIND_H

#include <new>
//#include "StatusType.h"
#include "library2.h"
using std::bad_alloc;

template <class K>
class UnionFind {
    int size;
    int* parent;
    int* size_of_group;
    K** pointers;
public:
    explicit UnionFind<K>(int size);
    ~UnionFind();
    StatusType Find(int i, K** pointer_to_return);
    StatusType Union(int p, int q);
};

template <class K>
UnionFind<K>::UnionFind(int size) : size(size) {
    try {
        parent = new int[size+1];
        size_of_group = new int[size+1];
        pointers = new K*[size+1];
        for (int i=1; i<=size; i++){
            parent[i] = i;
            size_of_group[i] = 1;
            pointers[i]=new K();
        }
    } catch (bad_alloc& b) {
        throw b;
    }
}

template <class K>
UnionFind<K>::~UnionFind() {
    delete[] parent;
    delete[] size_of_group;
    delete[] pointers;
}

template <class K>
StatusType UnionFind<K>::Union(int p, int q) {
    K* temp1;
    K* temp2;
    if ((p<=0)||(p>size)||(q<=0)||(q>size)) return INVALID_INPUT;
    if (size_of_group[p]>size_of_group[q]){
        size_of_group[p] += size_of_group[q];
        size_of_group[q] = 0;
        temp1=pointers[p];
        temp2=pointers[q];
        pointers[p] = *pointers[p]+*pointers[q];
        //delete temp1;
        //delete temp2;
        //pointers[q] = NULL;
        parent[q] = p;
    } else {
        size_of_group[q] += size_of_group[p];
        size_of_group[p] = 0;
        temp1=pointers[p];
        temp2=pointers[q];
        pointers[q] = *pointers[p]+*pointers[q];
        //delete temp1;
        //delete temp2;
        //pointers[p] = NULL;
        parent[p] = q;
    }
    return SUCCESS;
}

template <class K>
StatusType UnionFind<K>::Find(int i, K **pointer_to_return) {
    if ((i<=0)||(i>size)) return INVALID_INPUT;
    int curr = i;
    while (parent[curr]!=curr){ //find the root
        curr = parent[curr];
    }
    int sec_curr = i;
    while (parent[curr]!=curr){ //update all parents to be root
        curr = parent[curr];
    }
    *pointer_to_return = pointers[curr];
    return SUCCESS;
}


#endif //EX2_UNIONFIND_H
