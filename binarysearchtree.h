//
// Created by Predo on 21/03/2025.
//

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <stddef.h>

typedef struct BinaryTreeNode
{
    unsigned int data;
    struct BinaryTreeNode* parent;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
} BinaryTreeNode;

typedef struct BinarySearchTree {
    BinaryTreeNode* root;
    int size;
    size_t elementSize;
} BinarySearchTree;

extern void bstAdd(BinarySearchTree* bst, unsigned int data);

extern int bstFind(BinarySearchTree* bst, unsigned int data);

extern BinarySearchTree* bstCreate(size_t elementSize);

#endif //BINARYSEARCHTREE_H
