//
// Created by Predo on 23/12/2024.
//

#ifndef MAIN_H
#define MAIN_H

unsigned short int checkMovesFromAllDirections(char** matrix, int i, int j);
int checkWhiteSpaces(char** matrix, char** checkedStack, int* stackIndex, int* wanted, int depth);
int checkWantedAllowed(int* wanted);

// [row, col]
extern int directions[4][2];

#define DEBUG 1
#define MAX_DEPTH 1000

#endif //MAIN_H
