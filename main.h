//
// Created by Predo on 23/12/2024.
//

#ifndef MAIN_H
#define MAIN_H
#include "binarysearchtree.h"
#include "matrix.h"

struct Target {
    char wantedChar;
    int (*locations)[2];
    int nLocations;
};


unsigned short int checkMovesFromAllDirections(char** matrix, int i, int j);
int checkWantedAllowed(struct Target* wanted);
int checkWanted(char** matrix, struct Target* wanted);
int* locateChar(char** matrix, char wanted);
char*** checkAllMoves(char** matrix, int* n);
void loop(MatrixNode* matrixNode, BinarySearchTree* bst, struct Target* wanted, int depth, int optimizationNumber);
int getDistanceValue(char ** matrix, struct Target * target);

// [row, col]
extern int directions[4][2];

#define MAX_DEPTH 1500
#define OPTIMIZATION_NUMBER 2
#define SECONDS_PRINT_ANSWER 0

#endif //MAIN_H
