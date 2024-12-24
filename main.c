#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "matrix.h"
#include "shape.h"


void checkWhiteSpaces(char** matrix, int rows, int cols);
int test();

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
            }
            free(shapeCells);
        }
    }
    return temp;
}


// https://stackoverflow.com/questions/9846920/define-array-in-c