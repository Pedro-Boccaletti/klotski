//
// Created by Predo on 23/12/2024.
//

#include <stdio.h>

#include "matrix.h"


int checkBoundaries(int row, int col);
int runShape(char** matrix, int i, int j, char dummy, int direction);
int* checkDirections(char** matrix, int i, int j);

int test() {
    const char testMatrix2[3][3] = {
        {'x', 'x', 'x'},
        {'D', 0, 'A'},
        {'R', 'R', 'I'},
    };

    char** matrix2 = allocMatrix(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            setMatrixValue(matrix2, i, j, testMatrix2[i][j]);
        }
    }
    printMatrix(matrix2, 3, 3);
    int rShape = 0;
    int cShape = 2;
    char shape = matrix2[rShape][cShape];
    printf("%c\n", shape);
    for (int i = 0; i < 4; i++) {
        int b = runShape(matrix2, rShape, cShape, shape, i);
        printf("%d\n", b);
    }

    return 0;
}