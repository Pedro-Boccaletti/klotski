//
// Created by Predo on 23/12/2024.
//

#include "shape.h"
#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "main.h"

// allocates memory for the shape cells
int** allocShapeCells() {
    int matrixSize = MATRIX_ROWS * MATRIX_COLS;
    int** temp = (int**) malloc(matrixSize * sizeof(int*));
    for (int i = 0; i < matrixSize; i++) {
        temp[i] = NULL;
    }
    return temp;
}

// check if a cell has been visited
int checkCellBeenVisited(int** shapeCells, int row, int col) {
    for (int i = 0; i < MATRIX_ROWS * MATRIX_COLS; i++) {
        if (shapeCells[i] == NULL) {
            return 0;
        }
        if (shapeCells[i][0] == row && shapeCells[i][1] == col) {
            return 1;
        }
    }
    return 0;
}

void moveShape(char** matrix, int** shapeCells, char dummy, int direction) {
    for (int i = 0; i < MATRIX_ROWS * MATRIX_COLS; i++) {
        if (shapeCells[i] == NULL) {
            break;
        }
        int row = shapeCells[i][0];
        int col = shapeCells[i][1];
        matrix[row][col] = BLANK_SPACE;
    }
    for (int i = 0; i < MATRIX_ROWS * MATRIX_COLS; i++) {
        if (shapeCells[i] == NULL) {
            break;
        }
        int row = shapeCells[i][0];
        int col = shapeCells[i][1];
        int rowTowards = row + directions[direction][0];
        int colTowards = col + directions[direction][1];
        matrix[rowTowards][colTowards] = dummy;
    }
}

void deleteShapeCells(int** shapeCells) {
    for (int i = 0; i < MATRIX_ROWS * MATRIX_COLS; i++) {
        if (shapeCells[i] == NULL) {
            break;
        }
        free(shapeCells[i]);
    }
    free(shapeCells);
}

void getShapeCells(char** matrix, int i, int j, char dummy, int** shapeCells) {
    if (shapeCells == NULL) {
        return;
    }
    if (matrix[i][j] != dummy) {
        return;
    }
    for (int k = 0; k < MATRIX_ROWS * MATRIX_COLS; k++) {
        if (shapeCells[k] == NULL) {
            shapeCells[k] = (int*) malloc(2 * sizeof(int));
            if (shapeCells[k] == NULL) {
                if (DEBUG) { printf("problema alocando shapeCells[k]"); }
                return;
            }
            shapeCells[k][0] = i;
            shapeCells[k][1] = j;
            break;
        }
    }
    for (int k = 0; k < 4; k++) {
        int row = i + directions[k][0];
        int col = j + directions[k][1];
        if (checkCellBeenVisited(shapeCells, row, col)) {
            continue;
        }
        if (checkBoundaries(row, col)) {
            getShapeCells(matrix, row, col, dummy, shapeCells);
        }
    }
}

int checkShapeCanMove(char** matrix, int i, int j, int direction) {
    int** shapeCells = allocShapeCells();
    if (shapeCells == NULL) {
        if (DEBUG) { printf("problema alocando shapeCells"); }
        return 0;
    }
    char dummy = matrix[i][j];
    getShapeCells(matrix, i, j, dummy, shapeCells);
    for (int k = 0; k < MATRIX_ROWS * MATRIX_COLS; k++) {
        if (shapeCells[k] == NULL) {
            break;
        }
        int rowTowards = shapeCells[k][0] + directions[direction][0];
        int colTowards = shapeCells[k][1] + directions[direction][1];
        if (!checkBoundaries(rowTowards, colTowards)) {
            deleteShapeCells(shapeCells);
            return 0;
        }
        if (matrix[rowTowards][colTowards] != BLANK_SPACE && matrix[rowTowards][colTowards] != dummy) {
            deleteShapeCells(shapeCells);
            return 0;
        }
    }
    deleteShapeCells(shapeCells);
    return 1;
}