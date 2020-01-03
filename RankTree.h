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
public:
    StatusType find_by_index(int idx, generic_node<K> **ptr_to_node) const;
    StatusType SumHighest(int k, int *sum) const;
};

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
        generic_node<int> *node;
        this->find_by_index(this->tree_size-k, &node);
        if (node->right_son != NULL) *sum += node->right_son->subtree_sum;
        while (node!=this->root){
            if (node->father->left_son==node) *sum += *(node->father->data) + node->father->right_son->subtree_sum;
            node = node->father;
        }
        return SUCCESS;
    }
}

#endif //EX2_RANKTREE_H
