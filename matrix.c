//
// Created by Predo on 20/12/2024.
//

#include "matrix.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>

const char initialMatrix[MATRIX_ROWS][MATRIX_COLS] = {
    {'D', 'D', 0, 'P', 'P', 'I'},
    {'D', 'D', 0, 'P', 'I', 'M'},
    {'R', 'R', 'I', 'I', 'M', 'M'},
    {'T', 'T', 'O', 'I', 'C', 'N'},
    {'T', 'O', 'O', 'I', 'C', 'N'}
};

char** allocMatrix(int rows, int cols) {
    size_t charSize = sizeof(char);
    size_t rowSize = cols * charSize;
    size_t matrixSize = rows * sizeof(char*);
    char** matrix = (char**) malloc(matrixSize);
    if (matrix == NULL) {
        return NULL;
    }
    for (int i = 0; i< rows; i++) {
        matrix[i] = (char*) malloc(rowSize);
        if (matrix[i] == NULL) {
            deleteMatrix(matrix, i);
            return NULL;
        }
    }
    return matrix;
}

void deleteMatrix(char** matrix, int rows) {
    // free each row
    while (rows--) {
        free(*matrix++);
    }
    // free row pointers
    free(matrix);
}

void setMatrixValue(char** matrix, int row, int col, char value) {
    char* rowPointer = *(matrix + row);
    *(rowPointer + col) = value;
}

void printMatrix(char** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

char* matrixToString(char** matrix, int rows, int cols) {
    char* str = (char*) malloc(rows * cols * sizeof(char));
    if (str == NULL) {
        return NULL;
    }
    char* strPointer = str;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *strPointer++ = matrix[i][j];
        }
    }
    return str;
}

// check if a row and column are within the boundaries of the matrix
int checkBoundaries(int row, int col) {
    if (DEBUG) return row >= 0 && row < 3 && col < 3 && col >= 0;
    return row >= 0 && row < MATRIX_ROWS && col >= 0 && col < MATRIX_COLS;
}

void copyMatrix(char** matrix, char** newMatrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
}