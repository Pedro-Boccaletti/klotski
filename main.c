#include <stdio.h>
#include "matrix.h"
#define MAX_SIZE 2




int main(void)
{
    char** matrix = allocMatrix(MATRIX_ROWS, MATRIX_COLS);
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            setMatrixValue(matrix, i, j, initialMatrix[i][j]);
        }
    }
    printMatrix(matrix, MATRIX_ROWS, MATRIX_COLS);
    return 0;
}


// https://stackoverflow.com/questions/9846920/define-array-in-c