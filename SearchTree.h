#ifndef EX2_SEARCHTREE_H
#define EX2_SEARCHTREE_H

#include <iostream>
#include <string>
#include <cstdbool>
using std::string;
using std::ostream;
using std::endl;
using std::bad_alloc;

//-------------------defines section----------------------
#define MAX(a, b) ((a > b) ? a : b)

#include "StatusType.h"
#include "generic_node.h"
//--------------------------------------------------------

/// basic search tree class, supposed to be a base class for AVL tree
/// \tparam K - data class, need to support <,== operators and copy ctr'
template <class K>
class SearchTree
{
protected:
    generic_node<K> *root;
    int tree_size;
    StatusType find_rec(K data, generic_node<K> **ptr_to_node) const;
    StatusType swap_nodes(generic_node<K> *node1, generic_node<K> *node2);
    virtual void update_height(generic_node<K> *node);
    void to_array_inorder_rec(K **array, generic_node<K> *curr_node) const;
public:
    SearchTree<K>();
    StatusType find(K data, generic_node<K> **ptr_to_node) const;
    virtual StatusType insert(K &data);
    virtual StatusType remove(K data);
    void to_array_inorder(K **array) const;
    int get_tree_size() const;
};

/// Basic constructor for empty tree
template <class K>
SearchTree<K>::SearchTree() : root(NULL), tree_size(0){}

/// search for a node in the tree based on its key
/// \param data - key to search for
/// \param ptr_to_node - get an empty ptr to ptr. in the end of the function
/// the ptr will hold the node if there is one in the key, or the last
/// node in the search route if isn't.
/// \return INVALID INPUT if the data is NULL,
/// SUCCESS if there node with this data,
/// FAILURE otherwise
template <class K>
StatusType SearchTree<K>::find(K data, generic_node<K> **ptr_to_node) const{
    if (!data) return INVALID_INPUT;
    *ptr_to_node=root;
    if (root==NULL) return FAILURE;
    else {
        return find_rec(data, ptr_to_node);
    }
}

/// the recursive function that actually search for a node. check if the
/// current node has the required key, and if not try to check if it have son
/// and call itself to its correct son.
/// \param data - key to search for
/// \param ptr_to_node - ptr to ptr to the current node in the search route
/// \return SUCCESS if there node with this data, FAILURE otherwise
template <class K>
StatusType SearchTree<K>::find_rec(K data, generic_node<K> **ptr_to_node) const {
    if (*((*ptr_to_node)->data)==data) return SUCCESS;
    else{
        if ((data < *((*ptr_to_node)->data)) &&
        ((*ptr_to_node)->left_son != NULL)){
            *ptr_to_node=(*ptr_to_node)->left_son;
            return find_rec(data, ptr_to_node);
        }
        else if ((*((*ptr_to_node)->data) < data) &&
        ((*ptr_to_node)->right_son != NULL)) {
            *ptr_to_node=(*ptr_to_node)->right_son;
            return find_rec(data, ptr_to_node);
        }
        else {
            return FAILURE;
        }
    }
}

/// insert a new node to the tree
/// \param data - data for the new node
/// \return FAILURE if data already exist, ALLOCATION_ERROR if there was
/// allocation error, SUCCESS if everything went fine
template <class K>
StatusType SearchTree<K>::insert(K &data) {
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
            }
            this->tree_size++;
            return SUCCESS;
        } catch(bad_alloc& b){
            return ALLOCATION_ERROR;
        }
    }
}


/// remove a specific node in the tree
/// \param data - data of the pointer to remove
/// \return FAILURE if the data doesn't exist int the tree, SUCCESS otherwise
template <class K>
StatusType SearchTree<K>::remove(K data){
    generic_node<K> *last_node;
    StatusType res = this->find(data, &last_node);
    if (res==FAILURE) return FAILURE;
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
            this->remove(data);
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
            this->remove(data);
        }
    }
    this->tree_size--;
    return SUCCESS;
}

/// recursive function that update node's height based on its sons, and then
/// calls itself on his father.
/// \param node - a node to update its height
template <class K>
void SearchTree<K>::update_height(generic_node<K> *node) {
    if (node!=NULL){
        if ((node->left_son==NULL)&&(node->right_son==NULL)) node->height=0;
        else if (node->left_son==NULL) node->height=node->right_son->height+1;
        else if (node->right_son==NULL) node->height=node->left_son->height+1;
        else
            node->height =MAX(node->left_son->height,node->right_son->height)+1;
        if (node!=root) update_height(node->father);
    }
}

/// replace two nodes place in the tree. note: doesn't change their content,
/// only swap their connections to other nodes in the tree.
/// \param node1 - node to be swapped.
/// \param node2 - node to be swapped.
/// \return - SUCCESS if the swap succeed, FAILURE otherwise
template <class K>
StatusType SearchTree<K>::swap_nodes(generic_node<K> *node1,
        generic_node<K> *node2) {
    if (node2->father==node1) {
        generic_node<K> *father_placeholder = node1->father;
        generic_node<K> *leftson_placeholder = node2->left_son;
        generic_node<K> *rightson_placeholder = node2->right_son;
        node1->father = node2;
        if (node1->left_son == node2) {
            node2->left_son = node1;
            if (node1->right_son != NULL) node1->right_son->father = node2;
            node2->right_son = node1->right_son;
        } else if (node1->right_son == node2) {
            node2->right_son = node1;
            if (node1->left_son != NULL) node1->left_son->father = node2;
            node2->left_son = node1->left_son;
        }
        node2->father = father_placeholder;
        if (father_placeholder == NULL) root = node2;
        else if (father_placeholder->left_son == node1)
            father_placeholder->left_son = node2;
        else if (father_placeholder->right_son == node1)
            father_placeholder->right_son = node2;
        else return FAILURE;

        node1->left_son = leftson_placeholder;
        if (leftson_placeholder != NULL) {
            leftson_placeholder->father = node1;
        }

        node1->right_son = rightson_placeholder;
        if (rightson_placeholder != NULL) {
            rightson_placeholder->father = node1;
        }
    } else {
        generic_node<K> *father_placeholder = node1->father;
        generic_node<K> *leftson_placeholder = node1->left_son;
        generic_node<K> *rightson_placeholder = node1->right_son;

        //replace node2 with node1
        node1->father=node2->father;
        if (node2->father==NULL) root = node1;
        else if (node2->father->left_son==node2) node2->father->left_son=node1;
        else if (node2->father->right_son==node2)node2->father->right_son=node1;
        else return FAILURE;

        node1->left_son=node2->left_son;
        if (node2->left_son!=NULL){
            node2->left_son->father=node1;
        }

        node1->right_son=node2->right_son;
        if (node2->right_son!=NULL){
            node2->right_son->father=node1;
        }

        //replace node1 with node2
        node2->father=father_placeholder;
        if (father_placeholder==NULL) root = node2;
        else if (father_placeholder->left_son==node1)
            father_placeholder->left_son=node2;
        else if (father_placeholder->right_son==node1)
            father_placeholder->right_son=node2;
        else return FAILURE;

        node2->left_son=leftson_placeholder;
        if (leftson_placeholder!=NULL){
            leftson_placeholder->father=node2;
        }

        node2->right_son=rightson_placeholder;
        if (rightson_placeholder!=NULL){
            rightson_placeholder->father=node2;
        }
    }
    return SUCCESS;
}

/// return the size of the tree (number of total nodes)
/// \return - the size of the tree
template <class K>
int SearchTree<K>::get_tree_size() const {
    return this->tree_size;
}

/// insert all the tree's node's values ordered by their data
/// \param array - pointer to empty array of Ts. in the end of the recursive
/// process the array will hold the values.
template <class K>
void SearchTree<K>::to_array_inorder(K **array) const {
    if (root!=NULL) return to_array_inorder_rec(array, root);
}

/// recursive function the take inorder route on the tree and insert each
/// node to the given array
/// \param array - pointer to the current place in the array
/// \param curr_node -current node to check
template <class K>
void SearchTree<K>::to_array_inorder_rec(K **array, generic_node<K> *curr_node) const {
    if (!curr_node) return ;
    to_array_inorder_rec(array, curr_node->left_son);
    **array = *(curr_node->data);
    (*array)++;
    to_array_inorder_rec(array, curr_node->right_son);
}

#endif //EX2_SEARCHTREE_H
