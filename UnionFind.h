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
    int Find_root(int i);
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
        for (int i=0; i<=size; i++){
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
    for (int i=0; i<=size; i++){
        if (size_of_group[i]!=0) delete pointers[i];
    }
    delete[] pointers;
    delete[] parent;
    delete[] size_of_group;
}

template <class K>
StatusType UnionFind<K>::Union(int p, int q) {
    if ((p<=0)||(p>size)||(q<=0)||(q>size)) return INVALID_INPUT;
    K* temp1;
    K* temp2;
    int real_p = this->Find_root(p);
    int real_q = this->Find_root(q);
    if (real_p==real_q) return SUCCESS;
    if (size_of_group[real_p]>size_of_group[real_q]){
        size_of_group[real_p] += size_of_group[real_q];
        size_of_group[real_q] = 0;
        temp1=pointers[real_p];
        temp2=pointers[real_q];
        pointers[real_p] = *pointers[real_p]+*pointers[real_q];
        //pointers[q] = pointers[p];
        delete temp1;
        delete temp2;
        parent[real_q] = real_p;
    } else {
        size_of_group[real_q] += size_of_group[real_p];
        size_of_group[real_p] = 0;
        temp1=pointers[real_p];
        temp2=pointers[real_q];
        pointers[real_q] = *pointers[real_p]+*pointers[real_q];
        //pointers[p] = pointers[q];
        delete temp1;
        delete temp2;
        parent[real_p] = real_q;
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
    int tmp;
    while (parent[sec_curr]!=sec_curr){ //update all parents to be root
        tmp = parent[sec_curr];
        parent[sec_curr] = curr;
        sec_curr = tmp;
    }
    *pointer_to_return = pointers[curr];
    return SUCCESS;
}

template <class K>
int  UnionFind<K>::Find_root(int i){
    int curr = i;
    while (parent[curr]!=curr){ //find the root
        curr = parent[curr];
    }
    return curr;
}

#endif //EX2_UNIONFIND_H
