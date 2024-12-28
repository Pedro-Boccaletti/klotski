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
    size_t matrixSize = MATRIX_ROWS * MATRIX_COLS;
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
        free(shapeCells[i]);
    }
}

// run the shape and checks if the move is valid
int checkShapeCanMove(char** matrix, int i, int j, char dummy, int direction, int** shapeCells) {
    if (matrix[i][j] != dummy) {
        if (DEBUG > 1) printf("debug {i:%d, j:%d, dummy:%c, direction:%d} retornara -1\n", i, j, dummy, direction);
        return -1; // it's not a part of the shape
    }
    for (int k = 0; k < MATRIX_ROWS * MATRIX_COLS; k++) {
        if (shapeCells[k] && shapeCells[k][0] == i && shapeCells[k][1] == j) {
            return -1; // already visited
        }
        if (shapeCells[k] == NULL) {
            shapeCells[k] = (int*) malloc(2 * sizeof(int));
            if (shapeCells[k] == NULL) {
                printf("erro alocação");
            }
            shapeCells[k][0] = i;
            shapeCells[k][1] = j;
            break;
        }
    }
    // check neighbor cells
    for (int k = 0; k < 4; k++) {
        int neighborRow = i + directions[k][0];
        int neighborCol = j + directions[k][1];
        // if not a part of the board, don't check it
        if (!checkBoundaries(neighborRow, neighborCol)) {
            continue;
        }
        if (checkCellBeenVisited(shapeCells, neighborRow, neighborCol)) {
            continue;
        }
        int a = checkShapeCanMove(matrix, neighborRow, neighborCol, dummy, direction, shapeCells);
        if (!a) {
            if (DEBUG > 1) printf("debug {i:%d, j:%d, dummy:%c, direction:%d} retornara 0\n", i, j, dummy, direction);
            return 0;
        }

    }

    int rowTowards = i + directions[direction][0];
    int colTowards = j + directions[direction][1];
    if (checkBoundaries(rowTowards, colTowards)) {
        if (matrix[rowTowards][colTowards] == BLANK_SPACE || matrix[rowTowards][colTowards] == dummy) {
            if (DEBUG > 1) printf("debug {i:%d, j:%d, dummy:%c, direction:%d} retornara 1\n", i, j, dummy, direction);

            return 1; // can move in that direction
        }
    }
    // can't either because its on the edge (first if) or it is not a white space nor the shape itself
    if (DEBUG > 1) printf("debug {i:%d, j:%d, dummy:%c, direction:%d} retornara 0\n", i, j, dummy, direction);
    return 0;
}
