//
// Created by Predo on 20/12/2024.
//

#include "matrix.h"

#include <stdlib.h>

char** createMatrix(int rows, int cols) {
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
