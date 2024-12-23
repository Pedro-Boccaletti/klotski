#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int checkBoundaries(int row, int col);
int runShape(char** matrix, int i, int j, char dummy, int direction, int** shapeCells);
int* checkDirections(char** matrix, int i, int j);
int checkCellBeenVisited(int** shapeCells, int row, int col);
int test();


void checkMoves(char** matrix, int rows, int cols);

int main(void)
{
    /*
    char** matrix = allocMatrix(MATRIX_ROWS, MATRIX_COLS);
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            setMatrixValue(matrix, i, j, initialMatrix[i][j]);
        }
    }
    printMatrix(matrix, MATRIX_ROWS, MATRIX_COLS);
    */
    //printMatrix(matrix, 3, 3);
    //checkMoves(matrix, 3, 3);
    test();
    return 0;
}

// [row, col]
int directions[4][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};

void checkMoves(char** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                int* possibleMoves = checkDirections(matrix, i, j);
                if (possibleMoves == NULL) {
                    printf("problema alocação de memoria");
                    return;
                }
                for (int k = 0; k < 4; k++) {
                    if (possibleMoves[k]) {
                        // create new matrix, move the shape and call again recursively
                        printf("move %d - %d in direction {%d, %d}\n", i, j, directions[k][0], directions[k][1]);
                    }
                }
                free(possibleMoves);
            }
        }
    }
}


int ** allocShapeCells(void);

// return an array of pointers related to all directions
int* checkDirections(char** matrix, int i, int j) {
    int* temp = (int*) malloc(4 * sizeof(int));
    if (temp == NULL) {
        return NULL;
    }
    for (int k = 0; k < 4; k++) {
        temp[k] = 0;
        int rowDummy = i - directions[k][0];
        int colDummy = j - directions[k][1];
        if (checkBoundaries(rowDummy, colDummy) && matrix[rowDummy][colDummy] != 0) {
            int** shapeCells = allocShapeCells();
            int possible = runShape(matrix, rowDummy, colDummy, matrix[rowDummy][colDummy], k, shapeCells);
            if (possible) {
                temp[k] = 1;
            }
            free(shapeCells);
        }
    }
    return temp;
}

// check if a row and column are within the boundaries of the matrix
int checkBoundaries(int row, int col) {
    //return row >= 0 && row < MATRIX_ROWS && col >= 0 && col < MATRIX_COLS;
    return row >= 0 && row < 3 && col < 3 && col >= 0;
}

// run the shape and checks if the move is valid
int runShape(char** matrix, int i, int j, char dummy, int direction, int** shapeCells) {
    if (matrix[i][j] != dummy) {
        printf("debug {i:%d, j:%d, dummy:%c, direction:%d} retornara -1\n", i, j, dummy, direction);
        return -1; // it's not a part of the shape
    }
    for (int k = 0; k < MATRIX_ROWS * MATRIX_COLS; k++) {
        if (shapeCells[k] == NULL) {
            shapeCells[k] = (int*) malloc(2 * sizeof(int));
            shapeCells[k][0] = i;
            shapeCells[k][1] = j;
            break;
        }
        if (shapeCells[k][0] == i && shapeCells[k][1] == j) {
            return -1; // already visited
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
        int a = runShape(matrix, neighborRow, neighborCol, dummy, direction, shapeCells);
        if (!a) {
            printf("debug {i:%d, j:%d, dummy:%c, direction:%d} retornara 0\n", i, j, dummy, direction);
            return 0;
        }

    }

    int rowTowards = i + directions[direction][0];
    int colTowards = j + directions[direction][1];
    if (checkBoundaries(rowTowards, colTowards)) {
        if (matrix[rowTowards][colTowards] == 0 || matrix[rowTowards][colTowards] == dummy) {
            printf("debug {i:%d, j:%d, dummy:%c, direction:%d} retornara 1\n", i, j, dummy, direction);

            return 1; // can move in that direction
        }
    }
    // can't either because its on the edge (first if) or it is not a white space nor the shape itself
    printf("debug {i:%d, j:%d, dummy:%c, direction:%d} retornara 0\n", i, j, dummy, direction);
    return 0;
}

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


// https://stackoverflow.com/questions/9846920/define-array-in-c