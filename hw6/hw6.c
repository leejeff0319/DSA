#include "bitree.h"
#include <stdio.h>
#include <stdlib.h>


// Recursion to count the leaf nodes for the tree
int leaves_recursion(BiTreeNode *node) {
    if (node == NULL) {                 // if node is empty
        return 0;                       // return 0 for False, (also good for counting)
    }
    if (bitree_left(node) == NULL &&    // if the node has no left or right children
        bitree_right(node) == NULL) {   // In other words, if the node is a leaf node
        return 1;                       // return 1 for True, (also good for counting)
    }
    return leaves_recursion(node->left) + leaves_recursion(node->right); 
}

int count_leaves (BiTree *tree) {
    return leaves_recursion(tree->root);
}

// Recursion to count number of non-leaf nodes in the tree
int non_leaves_recursion (BiTreeNode *node) {
    if (node == NULL) {                                 // if node is empty
        return 0;                                       // return 0
    }
    if (node->left != NULL || node->right != NULL){     // if either child node isn't empty -> it's not a leaf node
        return 1 + non_leaves_recursion(node->left) + non_leaves_recursion(node->right);
    }
    return 0;
}

int count_non_leaves (BiTree *tree) {
    return non_leaves_recursion(tree->root);
}

// Returns the height of the tree
int get_height_recursion (BiTreeNode *node) {
    if (node == NULL) {
        return 0;
    }

    // Recursion to separately get heights of left side of binary tree as well as right side
    int left_height = get_height_recursion(node->left);
    int right_height = get_height_recursion(node->right);

    // if left > right, return left; else return right
    return 1 + (left_height > right_height ? left_height : right_height);   // height + 1 (for root node)
}

int get_height(BiTree *tree) {
    return get_height_recursion(tree->root);
}

// print pre order
void print_pre_order_recursion (BiTreeNode *node, void (*print)(const void *data)) {
    if (node == NULL) {
        return;
    }

    // root node
    print(bitree_data(node));

    // recursion to print left and right nodes in order after the root node (post-traversally)
    print_pre_order_recursion(bitree_left(node), print);
    print_pre_order_recursion(bitree_right(node), print);
}

void print_pre_order (BiTree *tree, void (*print)(const void*data)) {
    print_pre_order_recursion(tree->root, print);
}

void print_node(const void *data) {
    printf("%d ", *(int *)data);
}

// print in-order (from left to right regardless of height)
void print_in_order_recursion(BiTreeNode *node, void (*print)(const void *data)) {
    if (node == NULL) {
        return;
    }

    // Recursively traverse the left subtree first
    print_in_order_recursion(bitree_left(node), print);

    // then the root node
    print(bitree_data(node));

    // finally, traverse the right subtree
    print_in_order_recursion(bitree_right(node), print);
}

void print_in_order(BiTree *tree, void (*print)(const void *data)) {
    print_in_order_recursion(tree->root, print);
}

// print post-order
void print_post_order_recursion(BiTreeNode *node, void (*print)(const void *data)) {
    if (node == NULL) {
        return;
    }

    // Recursively traverse the left subtree first
    print_post_order_recursion(bitree_left(node), print);

    // then, traverse the right subtree
    print_post_order_recursion(bitree_right(node), print);

    // finally, the root node
    print(bitree_data(node));
}

void print_post_order(BiTree *tree, void (*print)(const void *data)) {
    print_post_order_recursion(tree->root, print);
}

// Remove Leaves
BiTreeNode *remove_leaves_recursion(BiTreeNode **node){                 // use double pointers to directly modify the tree
    if (node == NULL || *node == NULL) {
        return NULL;
    }

    if ((*node)->left == NULL && (*node)->right == NULL) {              // if the current node is a leaf node
        BiTreeNode *temp = *node;                                       // store current node address to another pointer
        *node = NULL;                                                   // remove the node
        free(temp);                                                     // free allocated memory
        return NULL;
    }

    // use recursion to repeat the process for all nodes until no more leaf nodes exist on the tree
    (*node)->left = remove_leaves_recursion(&((*node)->left));
    (*node)->right = remove_leaves_recursion(&((*node)->right));

    // Remove nodes again after the first set of leaves has been removed
    if ((*node)->left == NULL && (*node)->right == NULL) {
        BiTreeNode *temp = *node;
        *node = NULL;
        free(temp);
        return NULL;
    }

    return *node;
}

void remove_leaves(BiTree *tree){
    tree->root  = remove_leaves_recursion(&(tree->root));
}

// Ceates an integer on the heap
int* create_int(int value) {
    int* new_int = (int*)malloc(sizeof(int));
    *new_int = value;
    return new_int;
}

// Free function for bitree_init
void free_int(void* data) {
    free(data);
}

int main() {
    // Initialize the 2 trees given in the assignment
    BiTree tree1, tree2;
    BiTreeNode *node;
    bitree_init(&tree1, free_int);
    bitree_init(&tree2, free_int);

    // Insert for nodes tree1
    bitree_ins_left(&tree1, NULL, create_int(1));
    node = tree1.root;
    bitree_ins_left(&tree1, node, create_int(2));
    bitree_ins_left(&tree1, node->left, create_int(4));
    bitree_ins_left(&tree1, node->left->left, create_int(7));
    bitree_ins_right(&tree1, node, create_int(3));
    bitree_ins_left(&tree1, node->right, create_int(5));
    bitree_ins_right(&tree1, node->right, create_int(6));
    bitree_ins_right(&tree1, node->right->right, create_int(8));
    bitree_ins_right(&tree1, node->right->right->right, create_int(9));

    // Insert for nodes tree2
    bitree_ins_left(&tree2, NULL, create_int(6));
    node = tree2.root;
    bitree_ins_left(&tree2, node, create_int(4));
    bitree_ins_left(&tree2, node->left, create_int(2));
    bitree_ins_right(&tree2, node->left, create_int(5));
    bitree_ins_left(&tree2, node->left->left, create_int(1));
    bitree_ins_right(&tree2, node->left->left, create_int(3));
    bitree_ins_right(&tree2, node, create_int(8));
    bitree_ins_left(&tree2, node->right, create_int(7));
    bitree_ins_right(&tree2, node->right, create_int(9));

    // count leaves
    int leaves1 = count_leaves(&tree1);
    int leaves2 = count_leaves(&tree2);
    printf("Number of leaves in tree1: %d\n", leaves1);
    printf("Number of leaves in tree2: %d\n", leaves2);

    // count non-leave nodes
    int nonLeaves1 = count_non_leaves(&tree1);
    int nonLeaves2 = count_non_leaves(&tree2);
    printf("Number of non-leaf nodes in tree1: %d\n", nonLeaves1);
    printf("Number of non-leaf nodes in tree2: %d\n", nonLeaves2);

    // get height of tree
    int height1 = get_height(&tree1);
    int height2 = get_height(&tree2);
    printf("Height of tree1: %d\n", height1);
    printf("Height of tree2: %d\n", height2);

    // print pre order
    printf("Print pre order\n");
    print_pre_order(&tree1, print_node);
    printf("\n");
    print_pre_order(&tree2, print_node);
    printf("\n");

    // print in order
    printf("Print in order\n");
    print_in_order(&tree1, print_node);
    printf("\n");
    print_in_order(&tree2, print_node);
    printf("\n");

    // print post order
    printf("Print post order\n");
    print_post_order(&tree1, print_node);
    printf("\n");
    print_post_order(&tree2, print_node);
    printf("\n");

    // remove leaves
    printf("Remove all leaves of the trees\n");
    remove_leaves(&tree1);
    remove_leaves(&tree2);

    // print pre order
    printf("Print pre order\n");
    print_pre_order(&tree1, print_node);
    printf("\n");
    print_pre_order(&tree2, print_node);
    printf("\n");

    // print in order
    printf("Print in order\n");
    print_in_order(&tree1, print_node);
    printf("\n");
    print_in_order(&tree2, print_node);
    printf("\n");

    // print post order
    printf("Print post order\n");
    print_post_order(&tree1, print_node);
    printf("\n");
    print_post_order(&tree2, print_node);
    printf("\n");

    // Destroy the trees to clean up
    bitree_destroy(&tree1);
    bitree_destroy(&tree2);
    
    return 0;
}