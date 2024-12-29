#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "matrix.h"
#include "shape.h"
#include "stack.h"


int checkWanted(char** matrix, int* wanted);
int test(char**);

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
    int a = checkWhiteSpaces(matrix, testedStack, &stackIndex, wanted, 0);
    printf("%d\n", a);
    return 0;
    if (test(testedStack)) {
        return 1;
    }
    return 0;
}

// [row, col]
int directions[4][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};

int checkWhiteSpaces(char** matrix, char** checkedStack, int* stackIndex, int* wanted, int depth) {
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
    char* str = matrixToString(matrix, MATRIX_ROWS, MATRIX_COLS);
    if (contains(checkedStack, stackIndex, str)) {
        if (DEBUG) printf("debug {str:%s} already in stack\n", str);
        free(str);
        return 0;
    }
    push(checkedStack, stackIndex, str);
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            if (matrix[i][j] == BLANK_SPACE) {
                if (DEBUG) printf("debug {i:%d, j:%d} chamara checkMovesFromAllDirections\n", i, j);
                unsigned short int a = checkMovesFromAllDirections(matrix, i, j);
                if (DEBUG) printf("debug {i:%d, j:%d} checkMovesFromAllDirections retornou %d\n", i, j, a);
                for (int k = 0; k < 4; k++) {
                    if (a & (1 << k)) {
                        int rowDummy = i - directions[k][0];
                        int colDummy = j - directions[k][1];
                        int** shapeCells = allocShapeCells();
                        if (shapeCells == NULL) {
                            if (DEBUG) { printf("problema alocando shapeCells"); }
                            return -1;
                        }
                        getShapeCells(matrix, rowDummy, colDummy, matrix[rowDummy][colDummy], shapeCells);
                        char** newMatrix = allocMatrix(MATRIX_ROWS, MATRIX_COLS);
                        if (newMatrix == NULL) {
                            if (DEBUG) { printf("problema alocando newMatrix"); }
                            return -1;
                        }
                        copyMatrix(matrix, newMatrix, MATRIX_ROWS, MATRIX_COLS);
                        moveShape(newMatrix, shapeCells, matrix[rowDummy][colDummy], k);
                        deleteShapeCells(shapeCells);
                        checkWhiteSpaces(newMatrix, checkedStack, stackIndex, wanted, depth + 1);
                    }
                }
            }
        }
    }
    deleteMatrix(matrix, MATRIX_ROWS);
    return 0;
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