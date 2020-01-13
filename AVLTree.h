#ifndef EX2_AVLTREE_H
#define EX2_AVLTREE_H

#include "SearchTree.h"
using std::bad_alloc;

/// implementation of AVL tree as learned in Data Structures 1, winter 19/20.
/// inherit from SearchTree class
/// \tparam K - data class, need to support <,== operators and copy ctr'
template <class K>
class AVLTree : public SearchTree<K>{
    int bf(generic_node<K> *node);
    StatusType right_roll(generic_node<K> *B);
    StatusType left_roll(generic_node<K> *A);
    StatusType fix_avl_struct(generic_node<K> *node);
    void free_postorder_rec(generic_node<K> *curr_node);
    public:
    AVLTree<K>();
    ~AVLTree<K>();
    StatusType insert(K& data) override;
    StatusType insert(K& data, generic_node<K> **ptr_to_node);
    StatusType remove(K data) override;
    StatusType remove_node(generic_node<K> *last_node, bool keep_avl_struct=true);
};

/// constructor for empty tree
template <class K>
AVLTree<K>::AVLTree() : SearchTree<K>() {}


/// destructor for AVLTree, calls recursive removal of all nodes.
template <class K>
AVLTree<K>::~AVLTree(){
    free_postorder_rec(this->root);
}

/// recursive removal of all nodes in the tree in postorder route.
/// \param curr_node -current node to remove after calling itself on its sons
template <class K>
void AVLTree<K>::free_postorder_rec(generic_node<K> *curr_node) {
    if (!curr_node) return ;
    free_postorder_rec(curr_node->left_son);
    free_postorder_rec(curr_node->right_son);
    remove_node(curr_node, false);
}

/// wrapper for insert function, when one doesn't need the pointer to the node
/// \param data - data for the new node
/// \return FAILURE if data already exist, SUCCESS if everything went fine
template <class K>
StatusType AVLTree<K>::insert(K &data) {
    generic_node<K> *last_node;
    return insert(data, &last_node);
}

/// insert a new node to the tree
/// \param data - data for the new node
/// \param ptr_to_node - empty pointer, after the function return it will
/// point to the new node in the tree
/// \return FAILURE if data already exist, ALLOCATION_ERROR if there was
/// allocation error, SUCCESS if everything went fine
template <class K>
StatusType AVLTree<K>::insert(K &data, generic_node<K> **ptr_to_node) {
    generic_node<K> *last_node;
    StatusType res = this->find(data, &last_node);
    if (res==SUCCESS) return FAILURE; //data already exist
    else {
        try{
            auto new_node = new generic_node<K>(&data);
            if (this->root==NULL){
                this->root = new_node;
            }
            else {
                if (data < *(last_node->data)){
                    last_node->left_son = new_node;
                    new_node->father = last_node;
                } else{
                    last_node->right_son = new_node;
                    new_node->father = last_node;
                }
                this->update_height(last_node);
                fix_avl_struct(last_node);
            }
            this->tree_size++;
            *ptr_to_node = new_node;
            return SUCCESS;
        } catch(bad_alloc& b){
            return ALLOCATION_ERROR;
        }
    }
}

/// remove a specific node in the tree
/// \param data - key of the pointer to remove
/// \return FAILURE if the data doesn't exist int the tree, SUCCESS otherwise
template <class K>
StatusType AVLTree<K>::remove(K data){
    generic_node<K> *last_node;
    StatusType res = this->find(data, &last_node);
    if (res==FAILURE) return FAILURE;
    return remove_node(last_node);
}

/// remove a specific node in the tree
/// \param last_node - pointer to the node in the tree to remove
/// \param keep_avl_struct - either to do rolls in order to keep the AVL
/// structure or not, default true
/// \return INVALID_INPUT if the pointer is empty, SUCCESS otherwise
template <class K>
StatusType AVLTree<K>::remove_node(generic_node<K> *last_node,
        bool keep_avl_struct){
    if (last_node==NULL) return INVALID_INPUT;
    bool need_avl_fix = (last_node->father!=NULL);
    if (this->root==last_node){
        if ((last_node->right_son == NULL) && (last_node->left_son == NULL)) {
            this->root=NULL;
            delete last_node;
        } else if ((last_node->right_son == NULL) &&
        (last_node->left_son != NULL)) {
            this->root=last_node->left_son;
            last_node->left_son->father=NULL;
            delete(last_node);
        } else if ((last_node->right_son != NULL) &&
        (last_node->left_son == NULL)) {
            this->root=last_node->right_son;
            last_node->right_son->father=NULL;
            delete(last_node);
        } else {
            generic_node<K> *switch_node;
            switch_node = last_node->right_son;
            while (switch_node->left_son != NULL) {
                switch_node = switch_node->left_son;
            }
            this->swap_nodes(last_node, switch_node);
            this->tree_size++;
            this->remove_node(last_node);
        }
    } else {
        generic_node<K> *father = last_node->father;
        if ((last_node->right_son == NULL) && (last_node->left_son == NULL)) {
            last_node->height--;
            this->update_height(last_node->father);
            if (father->left_son == last_node) father->left_son = NULL;
            else if (father->right_son == last_node) father->right_son = NULL;
            delete(last_node);
        } else if ((last_node->right_son==NULL) && (last_node->left_son!=NULL)){
            last_node->height--;
            this->update_height(last_node->father);
            if (father->left_son == last_node) {
                father->left_son = last_node->left_son;
                last_node->left_son->father = father;
            }
            else if (father->right_son == last_node) {
                father->right_son = last_node->left_son;
                last_node->left_son->father = father;
            }
            delete(last_node);
        } else if ((last_node->right_son!=NULL) && (last_node->left_son==NULL)){
            last_node->height--;
            this->update_height(last_node->father);
            if (father->left_son == last_node) {
                father->left_son = last_node->right_son;
                last_node->right_son->father = father;
            }
            else if (father->right_son == last_node) {
                father->right_son = last_node->right_son;
                last_node->right_son->father = father;
            }
            delete(last_node);
        } else {
            generic_node<K> *switch_node;
            switch_node = last_node->right_son;
            while (switch_node->left_son != NULL) switch_node = switch_node->left_son;
            this->swap_nodes(last_node, switch_node);
            this->tree_size++;
            this->remove_node(last_node);
        }
        if ((need_avl_fix)&&(keep_avl_struct)) fix_avl_struct(father);
    }
    this->tree_size--;
    return SUCCESS;
}

/// calculate the bf value of node: left son's height - right son's height
/// note: empty son counts as -1
/// \param node - node to calculate its bf value
/// \return the bf value
template <class K>
int AVLTree<K>::bf(generic_node<K> *node) {
    if ((node->left_son==NULL)&&(node->right_son==NULL)) return 0;
    else if (node->left_son==NULL) return (-1) - node->right_son->height;
    else if (node->right_son==NULL) return node->left_son->height - (-1);
    else return node->left_son->height - node->right_son->height;
}

/// doing a right roll like the one described in tutorial 5 slide 4
/// \param B - the node with the 2 or -2 bf
/// \return INVALID_INPUT if the node is not valid for right roll,
/// SUCCESS otherwise
template <class K>
StatusType AVLTree<K>::right_roll(generic_node<K> *B) {
    if (B==NULL) return INVALID_INPUT;
    if (B->left_son==NULL) return INVALID_INPUT;
    generic_node<K> * A = B->left_son;
    //move Ar to B
    B->left_son = A->right_son;
    if (A->right_son!=NULL) A->right_son->father = B;
    //put A instead of B in top
    if (B!=this->root) {
        if (B->father->left_son == B) B->father->left_son = A;
        else B->father->right_son = A;
        A->father = B->father;
    } else {
        this->root=A;
        A->father=NULL;
    }
    //make B son of A
    A->right_son=B;
    B->father=A;

    this->update_height(B);
    return SUCCESS;
}

/// doing a left roll as described in tutorial 5 slide 4
/// \param A - the node with the 2 or -2 bf
/// \return INVALID_INPUT if the node is not valid for left roll,
/// SUCCESS otherwise
template <class K>
StatusType AVLTree<K>::left_roll(generic_node<K> *A) {
    if (A==NULL) return INVALID_INPUT;
    if (A->right_son==NULL) return INVALID_INPUT;
    generic_node<K> * B = A->right_son;
    //move Bl to A
    A->right_son = B->left_son;
    if (B->left_son!=NULL) B->left_son->father = A;
    //put B instead of A in top
    if (A!=this->root){
        if (A->father->left_son==A) A->father->left_son=B;
        else A->father->right_son=B;
        B->father=A->father;
    } else {
        this->root=B;
        B->father=NULL;
    }
    //make A son of B
    B->left_son=A;
    A->father=B;

    this->update_height(A);
    return SUCCESS;
}

/// implementing the rolling algorithm for keeping the AVL structure
/// \param node - node to check if he hold the AVL criteria
/// \return INVALID_INPUT if the pointer is empty, SUCCESS otherwise
template <class K>
StatusType AVLTree<K>::fix_avl_struct(generic_node<K> *node) {
    if (node==NULL) return INVALID_INPUT;
    //TODO: add stop criteria according to distinction 4
    int curr_bf = this->bf(node);
    if (curr_bf==2) {
        if (this->bf(node->left_son)==-1) {//LR roll
            this->left_roll(node->left_son);
            this->right_roll(node);
        } else if (this->bf(node->left_son)>=0) {//LL roll
            this->right_roll(node);
        }
    }
    if (curr_bf==-2) {
        if (this->bf(node->right_son) == 1) {//RL roll
            this->right_roll(node->right_son);
            this->left_roll(node);
        } else if (this->bf(node->right_son) <= 0) {//RR roll
            this->left_roll(node);
        }
    }
    if (node!=this->root) fix_avl_struct(node->father);
    return SUCCESS;
}

#endif //EX2_AVLTREE_H
