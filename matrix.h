//
// Created by Predo on 20/12/2024.
//

#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_ROWS 5
#define MATRIX_COLS 6

void deleteMatrix(char** matrix, int rows);

extern const char initialMatrix[MATRIX_ROWS][MATRIX_COLS];

char** allocMatrix(int rows, int cols);

void setMatrixValue(char** matrix, int row, int col, char value);

void printMatrix(char** matrix, int rows, int cols);

int checkBoundaries(int row, int col);

#endif //MATRIX_H


