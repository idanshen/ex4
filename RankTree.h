//
// Created by User on 1/2/2020.
//

#ifndef EX2_RANKTREE_H
#define EX2_RANKTREE_H

#include "AVLTree.h"

template <class K>
class RankTree : public AVLTree<K>{
    void update_height(generic_node<K> *node);
    StatusType find_by_index_rec(int idx, generic_node<K> **ptr_to_node) const;
    StatusType fill_empty_tree_rec(generic_node<K>* node,K** arr1,K** arr2);
public:
    RankTree<K>();
    explicit RankTree<K>(int n);
    StatusType find_by_index(int idx, generic_node<K> **ptr_to_node) const;
    StatusType SumHighest(int k, int *sum) const;
    StatusType build_empty_tree(generic_node<K>* node,int levels,int height,int* leaves);
    StatusType fill_empty_tree(K** arr1,K** arr2);
    friend RankTree<K> operator+(const RankTree<K> &t1, const RankTree<K> &t2);

};
template <class K>
RankTree<K>::RankTree():AVLTree<K>() {}
///recursively build a tree with empty nodes
template <class K>
StatusType RankTree<K>::build_empty_tree(generic_node<K>* node,int levels,int height,int* leaves){
    if(height==levels){
        *leaves-=1;
        return SUCCESS;
    }
    if(height==levels-1 && *leaves==0){
        return SUCCESS;
    }
    generic_node<K>* new_node;
    try{
        new_node = new generic_node<K>(nullptr);
    }
    catch(bad_alloc &b){
        return ALLOCATION_ERROR;
    }
    if(!node->left_son){
        node->left_son=new_node;
        build_empty_tree(new_node,levels,height+1,leaves);
    }
    if(height==levels-1 && *leaves==0){
        return SUCCESS;
    }
    generic_node<K>* second_new_node;
    try{
        second_new_node = new generic_node<K>(nullptr);
    }
    catch(bad_alloc &b){
        return ALLOCATION_ERROR;
    }
    if(!node->right_son){
        node->right_son=second_new_node;
        build_empty_tree(second_new_node,levels,height+1,leaves);
    }

    return SUCCESS;



}
/// creates an empty tree with n nodes
template <class K>
RankTree<K>::RankTree(int n) : AVLTree<K>() {
    int counter=0;
    int num=n;
    generic_node<K>* new_node;
    while(num>0){
        num/=2;
        counter++;
    }
    counter+=1;
    int leaves=n-(2^(counter-1)-1);
    try{
        new_node = new generic_node<K>(nullptr);
        this->root=new_node;
    }
    catch(bad_alloc &b){}
    int height=1;
    build_empty_tree(this->root,counter,height,&leaves);

}

template <class K>
StatusType RankTree<K>::fill_empty_tree_rec(generic_node<K>* node,K** arr1,K** arr2){
    if(!arr1 || !arr2){
        return FAILURE;
    }
    if(!node->left_son && !node->right_son){
        if(*arr1 == nullptr){
            node->data=*arr2;
        }
        else if(*arr2 == nullptr){
            node->data=*arr1;
        }
        else if(*arr1<*arr2){
            node->data=*arr1;
            arr1++;
        }
        else{
            node->data=*arr2;
            arr2++;
        }
        update_height(node);
        return SUCCESS;
    }
    fill_empty_tree_rec(node->left_son,arr1,arr2);
    if(*arr1 == nullptr){
        node->data=*arr2;
    }
    else if(*arr2 == nullptr){
        node->data=*arr1;
    }
    else if(*arr1<*arr2){
        node->data=*arr1;
        arr1++;
    }
    else{
        node->data=*arr2;
        arr2++;
    }
    fill_empty_tree_rec(node->right_son,arr1,arr2);
    update_height(node);
    return SUCCESS;

}
template <class K>
StatusType RankTree<K>::fill_empty_tree(K** arr1,K** arr2){
    if(this->root== nullptr){
        return FAILURE;
    }
    return fill_empty_tree_rec(this->root,arr1,arr2);

}
/// recursive function that update node's height based on its sons, and then
/// calls itself on his father.
/// \param node - a node to update its height
template <class K>
void RankTree<K>::update_height(generic_node<K> *node) {
    if (node!=NULL){
        if ((node->left_son==NULL)&&(node->right_son==NULL)) {
            node->height=0;
            node->subtree_size = 1;
            node->subtree_sum = 0 + *(node->data);
        }
        else if (node->left_son==NULL) {
            node->height=node->right_son->height+1;
            node->subtree_size = node->right_son->subtree_size + 1;
            node->subtree_sum = node->right_son->subtree_sum + *(node->data);
        }
        else if (node->right_son==NULL) {
            node->height=node->left_son->height+1;
            node->subtree_size = node->left_son->subtree_size + 1;
            node->subtree_sum = node->left_son->subtree_sum + *(node->data);
        }
        else {
            node->height =MAX(node->left_son->height,node->right_son->height)+1;
            node->subtree_size = node->left_son->subtree_size + node->right_son->subtree_size + 1;
            node->subtree_sum = node->left_son->subtree_sum + node->right_son->subtree_sum + *(node->data);
        }
        if (node!=this->root) update_height(node->father);
    }
}

template <class K>
StatusType RankTree<K>::find_by_index(int idx, generic_node<K> **ptr_to_node) const{
    *ptr_to_node=this->root;
    if (this->root==NULL) return FAILURE;
    else {
        return find_by_index_rec(idx, ptr_to_node);
    }
}

template <class K>
StatusType RankTree<K>::find_by_index_rec(int idx, generic_node<K> **ptr_to_node) const {
    int left_size;
    if ((*ptr_to_node)->left_son != NULL){
        left_size = (*ptr_to_node)->left_son->subtree_size;
    } else {
        left_size = 0;
    }
    if (left_size+1==idx) return SUCCESS;
    else{
        if ((idx < left_size+1)&&((*ptr_to_node)->left_son != NULL)){
            *ptr_to_node=(*ptr_to_node)->left_son;
            return find_by_index_rec(idx, ptr_to_node);
        }
        else if ((left_size+1 < idx)&&((*ptr_to_node)->right_son != NULL)) {
            *ptr_to_node=(*ptr_to_node)->right_son;
            return find_by_index_rec(idx-left_size-1, ptr_to_node);
        }
        else {
            return FAILURE;
        }
    }
}

template <class K>
StatusType RankTree<K>::SumHighest(int k, int *sum) const {
    if (k<0) {
        return FAILURE;
    }
    else if (k==0) {
        *sum = 0;
        return SUCCESS;
    }
    else if (k==this->tree_size){
        *sum = this->root->subtree_sum;
        return SUCCESS;
    }
    else {
        *sum = 0;
        generic_node<K> *node;
        this->find_by_index(this->tree_size-k, &node);
        if (node->right_son != NULL) *sum += node->right_son->subtree_sum;
        while (node!=this->root){
            if (node->father->left_son==node) *sum += node->father->right_son->subtree_sum + *(node->father->data);
            node = node->father;
        }
        return SUCCESS;
    }
}

template <class K>
RankTree<K> operator+(const RankTree<K> &tree1, const RankTree<K> &tree2){
    int size1=tree1->get_tree_size();
    int size2=tree2->get_tree_size();
    K** arr1;
    K** arr2;
    RankTree<K>* new_tree;
    try{
        arr1=new K*[size1];
        arr2=new K*[size2];
        new_tree = new RankTree<K>(size1 + size2);

    }
    catch(bad_alloc &b){ return ALLOCATION_ERROR;}
    tree1->to_array_inorder(arr1);
    tree2->to_array_inorder(arr2);
    new_tree->fill_empty_tree(arr1,arr2);
    delete tree1;
    delete tree2; //TODO:?????
    return new_tree;


}
#endif //EX2_RANKTREE_H
