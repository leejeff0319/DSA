// bistree.h
#ifndef BISTREE_H
#define BISTREE_H

#include <stdlib.h>

// Binary tree node structure
typedef struct BiTreeNode_ {
    void *data;
    struct BiTreeNode_ *left;
    struct BiTreeNode_ *right;
} BiTreeNode;

// Binary tree structure
typedef struct BisTree_ {
    int size;
    int (*compare)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    BiTreeNode *root;
} BisTree;

// AVL tree node balance factors
#define AVL_LFT_HEAVY 1
#define AVL_BALANCED  0
#define AVL_RGT_HEAVY -1

// AVL tree node structure
typedef struct AvlNode_ {
    void *data;
    int hidden;
    int factor;
} AvlNode;

// Public interface
void bistree_init(BisTree *tree, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data));
void bistree_destroy(BisTree *tree);
int bistree_insert(BisTree *tree, const void *data);
int bistree_remove(BisTree *tree, const void *data);
int bistree_lookup(BisTree *tree, void **data);

// Binary tree macros
#define bitree_size(tree) ((tree)->size)
#define bitree_root(tree) ((tree)->root)
#define bitree_is_eob(node) ((node) == NULL)
#define bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)
#define bitree_data(node) ((node)->data)
#define bitree_left(node) ((node)->left)
#define bitree_right(node) ((node)->right)

#endif  // BISTREE_H

// Function to insert nodes
int bitree_ins_left(BisTree *tree, BiTreeNode *node, const void *data) {
    BiTreeNode *new_node;
    
    if (node == NULL && bitree_size(tree) != 0)
        return -1;
        
    if ((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
        return -1;
        
    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    
    if (node == NULL)
        tree->root = new_node;
    else
        node->left = new_node;
        
    tree->size++;
    return 0;
}

int bitree_ins_right(BisTree *tree, BiTreeNode *node, const void *data) {
    BiTreeNode *new_node;
    
    if (node == NULL && bitree_size(tree) != 0)
        return -1;
        
    if ((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
        return -1;
        
    new_node->data = (void *)data;
    new_node->left = NULL;
    new_node->right = NULL;
    
    if (node == NULL)
        tree->root = new_node;
    else
        node->right = new_node;
        
    tree->size++;
    return 0;
}

// Main program
#include <stdio.h>

// Comparison function for integers
int compare_ints(const void *key1, const void *key2) {
    int *k1 = (int *)key1;
    int *k2 = (int *)key2;
    return *k1 - *k2;
}

// Helper function to print the tree (in-order traversal)
void print_node(BiTreeNode *node, int level) {
    if (node == NULL) return;
    
    print_node(node->right, level + 1);
    
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%d\n", *(int *)((AvlNode *)node->data)->data);
    
    print_node(node->left, level + 1);
}

void print_tree(BisTree *tree) {
    printf("\nTree structure:\n");
    print_node(tree->root, 0);
    printf("\n");
}

int main() {
    BisTree tree1, tree2;
    int *data;
    
    // Initialize the trees
    bistree_init(&tree1, compare_ints, free);
    bistree_init(&tree2, compare_ints, free);
    
    // First tree: 1-2-3-4-5-6-7-8-9
    printf("Creating first tree:\n");
    int values1[] = {1, 2, 3, 4, 7, 5, 6, 8, 9};
    
    for (int i = 0; i < sizeof(values1)/sizeof(values1[0]); i++) {
        data = (int *)malloc(sizeof(int));
        *data = values1[i];
        if (bistree_insert(&tree1, data) != 0) {
            printf("Failed to insert %d\n", values1[i]);
            free(data);
        }
    }
    
    print_tree(&tree1);
    
    // Second tree: 6-4-8-2-5-7-9-1-3
    printf("\nCreating second tree:\n");
    int values2[] = {6, 4, 8, 2, 5, 7, 9, 1, 3};
    
    for (int i = 0; i < sizeof(values2)/sizeof(values2[0]); i++) {
        data = (int *)malloc(sizeof(int));
        *data = values2[i];
        if (bistree_insert(&tree2, data) != 0) {
            printf("Failed to insert %d\n", values2[i]);
            free(data);
        }
    }
    
    print_tree(&tree2);
    
    // Clean up
    bistree_destroy(&tree1);
    bistree_destroy(&tree2);
    
    return 0;
}