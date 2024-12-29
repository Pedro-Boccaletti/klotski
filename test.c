//
// Created by Predo on 23/12/2024.
//

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "shape.h"
#include "main.h"


int test(char** testedMatrix) {
    const char testMatrix2[3][3] = {
        {'B', 'x', 'x'},
        {'R', BLANK_SPACE, BLANK_SPACE},
        {'R', 'T', 'I'},
    };

    int wanted[3] = {'T', 1, 2};

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
    //printf("%c\n", shape);
    /*
    for (int i = 0; i < 4; i++) {
        int** shapeCells = allocShapeCells();
        int b = runShape(matrix2, rShape, cShape, shape, i, shapeCells);
        printf("%d\n", b);
    }
    */
    //checkMovesFromAllDirections(matrix2, 1, 1, testedMatrix, wanted);
    //return 0;
    if (!checkWantedAllowed(wanted)) {
        return 1;
    }
    int stackIndex = 0;
    checkWhiteSpaces(matrix2, testedMatrix, &stackIndex, wanted, 0);
    return 0;
}