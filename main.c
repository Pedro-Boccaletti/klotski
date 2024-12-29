#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "matrix.h"
#include "shape.h"
#include "stack.h"


void checkWhiteSpaces(char** matrix, int rows, int cols);
int test();

int main(void)
{
    char** matrix = allocMatrix(MATRIX_ROWS, MATRIX_COLS);
    if (matrix == NULL) {
        return 1;
    }
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            setMatrixValue(matrix, i, j, initialMatrix[i][j]);
        }
    }
    char** testedStack = allocStack();
    if (testedStack == NULL) {
        return 1;
    }
    int wanted[3] = {'D', MATRIX_ROWS - 1, MATRIX_COLS - 1};
    if (!checkWantedAllowed(wanted)) {
        return 1;
    }
    int stackIndex = 0;
    return 0;
}

// [row, col]
int directions[4][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};

void checkWhiteSpaces(char** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                int* possibleMoves = checkMovesFromAllDirections(matrix, i, j);
                if (possibleMoves == NULL) {
                    printf("problema alocação de memoria");
                    return;
                }
                for (int k = 0; k < 4; k++) {
                    if (possibleMoves[k]) {
                        // create new matrix, move the shape and call again recursively
                        if (DEBUG) {
                            printf("move %d - %d from direction {%d, %d}\n", i, j, directions[k][0], directions[k][1]);
                        }

                    }
                }
                free(possibleMoves);
            }
        }
    }
}


// return an array of pointers related to all directions
int* checkMovesFromAllDirections(char** matrix, int i, int j) {
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
            if (shapeCells == NULL) {
                return NULL;
            }
            int possible = checkShapeCanMove(matrix, rowDummy, colDummy, matrix[rowDummy][colDummy], k, shapeCells);
            if (possible) {
                temp[k] = 1;
                char** r = allocMatrix(MATRIX_ROWS, MATRIX_COLS);
                copyMatrix(matrix, r, MATRIX_ROWS, MATRIX_COLS);
                moveShape(r, shapeCells, matrix[rowDummy][colDummy], k);
                checkWhiteSpaces(r, MATRIX_ROWS, MATRIX_COLS);
                // tem que por algo para quebrar loop infinito
            }
            free(shapeCells);
        }
    }
    if (DEBUG) {
        printf("possibleDirections: %d\n", possibleDirections);
    }
    return possibleDirections;
}

int checkWanted(char** matrix, int* wanted) {
    return matrix[wanted[1]][wanted[2]] == wanted[0];
}

int checkWantedAllowed(int* const wanted) {
    return checkBoundaries(wanted[1], wanted[2]);
}

// https://stackoverflow.com/questions/9846920/define-array-in-c