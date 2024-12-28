//
// Created by Predo on 23/12/2024.
//

#include <stdio.h>

#include "matrix.h"


int checkBoundaries(int row, int col);
int checkShapeCanMove(char** matrix, int i, int j, char dummy, int direction, int** shapeCells);
int* checkMovesFromAllDirections(char** matrix, int i, int j);
int** allocShapeCells();
void checkWhiteSpaces(char** matrix, int rows, int cols);


int test() {
    const char testMatrix2[3][3] = {
        {'B', 'x', 'x'},
        {'R', BLANK_SPACE, BLANK_SPACE},
        {'R', 'T', 'I'},
    };

    char** matrix2 = allocMatrix(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            setMatrixValue(matrix2, i, j, testMatrix2[i][j]);
        }
    }
    printMatrix(matrix2, 3, 3);
    int rShape = 2;
    int cShape = 0;
    char shape = matrix2[rShape][cShape];
    printf("%c\n", shape);
    /*
    for (int i = 0; i < 4; i++) {
        int** shapeCells = allocShapeCells();
        int b = runShape(matrix2, rShape, cShape, shape, i, shapeCells);
        printf("%d\n", b);
    }
    */
    checkMovesFromAllDirections(matrix2, 1, 1);
    checkWhiteSpaces(matrix2, 3, 3);
    return 0;
}