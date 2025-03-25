//
// Created by Predo on 20/12/2024.
//

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


const char initialMatrix[MATRIX_ROWS][MATRIX_COLS] = {
    {'D', 'D', BLANK_SPACE, 'P', 'P', 'a'},
    {'D', 'D', BLANK_SPACE, 'P', 'b', 'M'},
    {'R', 'R', 'd', 'c', 'M', 'M'},
    {'T', 'T', 'O', 'e', 'C', 'N'},
    {'T', 'O', 'O', 'f', 'C', 'N'}
};

/*
 *this is the easy matrix
const char initialMatrix[MATRIX_ROWS][MATRIX_COLS] = {
    {'a', 'D', 'D', 'm'},
    {'b', 'D', 'D', 'l'},
    {'c', 'g', 'h', 'k'},
    {'d', 'f', 'i', 'j'},
    {'e', BLANK_SPACE, BLANK_SPACE, 'n'}
};
*/

char** allocMatrix(int rows, int cols) {
    size_t charSize = sizeof(char);
    size_t rowSize = cols * charSize;
    size_t matrixSize = rows * sizeof(char*);
    char** matrix = (char**) malloc(matrixSize);
    if (matrix == NULL) {
        return NULL;
    }
    for (int i = 0; i< rows; i++) {
        matrix[i] = (char*) malloc(rowSize);
        if (matrix[i] == NULL) {
            deleteMatrix(matrix, i);
            return NULL;
        }
    }
    return matrix;
}

void deleteMatrix(char** matrix, int rows) {
    // free each row
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    // free row pointers
    free(matrix);
}

void setMatrixValue(char** matrix, int row, int col, char value) {
    char* rowPointer = *(matrix + row);
    *(rowPointer + col) = value;
}

void printMatrix(char** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char c = matrix[i][j];
            if (c == BLANK_SPACE) {
                c = ' ';
            } else if (c >= 'a' && c <= 'z') {
                c = 'I';
            }
            printf("%c ", c);
        }
        printf("\n");
    }
}

// creates a unique string related to this state, to be compared latter
char* matrixToString(char** matrix, int rows, int cols) {
    char* str = (char*) malloc((rows * cols * sizeof(char) + 1));
    if (str == NULL) {
        printf("problem allocating memory for str\n");
        exit(-1);
        return NULL;
    }
    char* strPointer = str;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char c = matrix[i][j];
            if (c >= 'a' && c <= 'z') {
                c = 'a';
            }
            switch (c) {
                case BLANK_SPACE: c = '0'; break;
                case 'a': c = 'I'; break;
                case 'O': c = 'M'; break;
                case 'T': c = 'P'; break;
                case 'N': c = 'C'; break;
                default: break;
            }

            *strPointer++ = c;
        }
    }
    *strPointer = '\0';
    return str;
}

// check if a row and column are within the boundaries of the matrix
int checkBoundaries(int row, int col) {
    return row >= 0 && row < MATRIX_ROWS && col >= 0 && col < MATRIX_COLS;
}

void copyMatrix(char** matrix, char** newMatrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
}

MatrixNode* createMatrixNode(char** matrix) {
    MatrixNode* matrixNode = (MatrixNode*) malloc(sizeof(MatrixNode));
    if (matrixNode == NULL) {
        return NULL;
    }
    matrixNode->parent = NULL;
    matrixNode->data = matrix;
    return matrixNode;
}

void printAnswer(MatrixNode* node, unsigned int seconds) {
    if (node == NULL) {
        return;
    }
    printAnswer(node->parent, seconds);
    sleep(seconds);
    printMatrix(node->data, MATRIX_ROWS, MATRIX_COLS);
    printf("----------------------------------------------------\n");
}
