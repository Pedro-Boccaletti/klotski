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
    if (depth >= MAX_DEPTH) {
        return 0;
    }
    if (DEBUG) {
        printf("checkWhiteSpaces ultimo index do stack = %d\n", *stackIndex);
        printMatrix(matrix, MATRIX_ROWS, MATRIX_COLS);
    }
    if (checkWanted(matrix, wanted)) {
        printf("achou\n");
        exit(0);
        return 1;
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
unsigned short int checkMovesFromAllDirections(char** matrix, int i, int j) {
    unsigned short int possibleDirections = 0;
    for (int k = 0; k < 4; k++) {
        int rowDummy = i - directions[k][0];
        int colDummy = j - directions[k][1];
        int debuging = checkBoundaries(rowDummy, colDummy);
        if (DEBUG) {
            printf("rowDummy: %d, colDummy: %d\n", rowDummy, colDummy);
            printf("checkBoundaries: %d\t%c\n", debuging, debuging ? matrix[rowDummy][colDummy] : ' ');
        }
        if (checkBoundaries(rowDummy, colDummy) && matrix[rowDummy][colDummy] != BLANK_SPACE) {
            int possible = checkShapeCanMove(matrix, rowDummy, colDummy, k);
            possibleDirections |= possible << k;
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