//
// Created by Predo on 23/12/2024.
//

#ifndef MAIN_H
#define MAIN_H
#include "matrix.h"

struct Target {
    char wantedChar;
    int (*locations)[2];
    int nLocations;
};


unsigned short int checkMovesFromAllDirections(char** matrix, int i, int j);
int checkWantedAllowed(struct Target* wanted);
int checkWanted(char** matrix, struct Target* wanted);
int* locateWanted(char** matrix, char wanted);
char*** checkAllMoves(char** matrix, int* n);
void loop(struct Node* matrixNode, char** checkedStack, int* stackIndex, struct Target* wanted, int depth);

// [row, col]
extern int directions[4][2];

#define DEBUG 0
#define MAX_DEPTH 1000

#endif //MAIN_H
