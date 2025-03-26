//
// Created by Predo on 25/03/2025.
//

#include "binarysearchtree.h"
#include <stdlib.h>


// Function to create a new BinaryTreeNode
BinaryTreeNode* createNode(unsigned int data) {
    BinaryTreeNode* newNode = (BinaryTreeNode*) malloc(sizeof(BinaryTreeNode));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create a new BinarySearchTree
BinarySearchTree* bstCreate(size_t elementSize) {
    BinarySearchTree* bst = (BinarySearchTree*) malloc(sizeof(BinarySearchTree));
    if (bst == NULL) {
        return NULL;
    }
    bst->root = NULL;
    bst->size = 0;
    bst->elementSize = elementSize;
    return bst;
}

// Function to add a node to the BinarySearchTree
void bstAdd(BinarySearchTree* bst, unsigned int data) {
    BinaryTreeNode* newNode = createNode(data);
    if (newNode == NULL) {
        return;
    }

    if (bst->root == NULL) {
        bst->root = newNode;
    } else {
        BinaryTreeNode* current = bst->root;
        BinaryTreeNode* parent = NULL;

        while (current != NULL) {
            parent = current;
            if (data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        newNode->parent = parent;
        if (data < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }
    bst->size++;
}

// Function to find a node in the BinarySearchTree
int bstFind(BinarySearchTree* bst, unsigned int data) {
    BinaryTreeNode* current = bst->root;
    while (current != NULL) {
        if (data == current->data) {
            return 1; // Found
        } else if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return 0; // Not found
}