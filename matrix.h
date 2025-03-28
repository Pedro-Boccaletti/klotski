//
// Created by Predo on 20/12/2024.
//

#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_ROWS 5
#define MATRIX_COLS 6
#define BLANK_SPACE '-'
#define BLANK_SPACE_AMOUNT 2

#define FNV_OFFSET_BASIS 2166136261
#define FNV_PRIME 16777619
#include <stdint.h>

typedef struct MatrixNode {
    char** data;
    struct MatrixNode* parent;
    int distance;
} MatrixNode;

extern uint32_t hashMatrix(MatrixNode* matrixNode, int rows, int cols);

void deleteMatrix(char** matrix, int rows);

extern const char initialMatrix[MATRIX_ROWS][MATRIX_COLS];

char** allocMatrix(int rows, int cols);

void setMatrixValue(char** matrix, int row, int col, char value);

void printMatrix(char** matrix, int rows, int cols);

int checkBoundaries(int row, int col);

void copyMatrix(char** matrix, char** newMatrix, int rows, int cols);

MatrixNode* createMatrixNode(char** matrix);

void printAnswer(MatrixNode* node, unsigned int seconds);

#endif //MATRIX_H


