#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "matrix.h"
#include "shape.h"
#include "stack.h"


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

    struct Target* wanted = (struct Target*) malloc(sizeof(struct Target));
    wanted->wantedChar = 'D';
    int locations[1][2] = { MATRIX_ROWS - 1, MATRIX_COLS - 1 };
    wanted->locations = locations;
    wanted->nLocations = 1;
    if (!checkWantedAllowed(wanted)) {
        return 1;
    }
    int stackIndex = 0;

    struct Node* matrixNode = createMatrixNode(matrix);
    if (matrixNode == NULL) {
        return 1;
    }
    loop(matrixNode, testedStack, &stackIndex, wanted, 0, 0);
    return 0;
}

// [row, col]
int directions[4][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};

void loop(struct Node* matrixNode, char** checkedStack, int* stackIndex, struct Target* wanted, int depth, int o) {
    if (o > OPTIMIZATION_NUMBER) {
        deleteMatrix(matrixNode->data, MATRIX_ROWS);
        free(matrixNode);
        return;
    }
    char** matrix = matrixNode->data;
    if (depth >= MAX_DEPTH) {
        if (DEBUG > 1) printf("max depth reached\n");
        return;
    }
    if (DEBUG) {
        printf("checkWhiteSpaces ultimo index do stack = %d\n", *stackIndex);
        printMatrix(matrix, MATRIX_ROWS, MATRIX_COLS);
    }
    if (checkWanted(matrix, wanted)) {
        if (DEBUG) printf("achou\n");
        printAnswer(matrixNode, 0);
        printf("encontrado com %d movimentos\n", depth);
        exit(0);
    }
    int a = getDistanceValue(matrix, wanted);
    if (a == -1) {
        printf("deu BO getDistanceValue\n");
        exit(-2);
    }
    matrixNode->distance = a;
    if (matrixNode->parent) {
        if (matrixNode->parent->distance < matrixNode->distance) {
            o++;
        } else if (matrixNode->parent->distance > matrixNode->distance) {
            o = 0;
        }
    }

    char* str = matrixToString(matrix, MATRIX_ROWS, MATRIX_COLS);
    if (contains(checkedStack, stackIndex, str)) {
        if (DEBUG > 1) printf("debug {str:%s} already in stack\n", str);
        free(str);
        return;
    }
    push(checkedStack, stackIndex, str);
    int* a = locateWanted(matrix, wanted->wantedChar);
    //int distx = a[0] - wanted[1];
    //int disty = a[1] - wanted[2];
    free(a);

    // check all possible moves
    int nMoves = 0;
    char*** newMatrixes = checkAllMoves(matrix, &nMoves);
    for (int i = 0; i < nMoves; i++) {
        struct Node* node = createMatrixNode(newMatrixes[i]);
        node->parent = matrixNode;
        loop(node, checkedStack, stackIndex, wanted, depth + 1, o);
    }
    free(newMatrixes);
    deleteMatrix(matrix, MATRIX_ROWS);
    free(matrixNode);
}

char*** checkAllMoves(char** matrix, int* n) {
    size_t size = 8 * sizeof(char**);
    char*** allMoves = (char***) malloc(size);
    if (allMoves == NULL) {
        return NULL;
    }

    int checkedRow = -1;
    int checkedCol = -1;
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            if (matrix[i][j] == BLANK_SPACE && !(i == checkedRow && j == checkedCol)) {
                checkedRow = i;
                checkedCol = j;
                if (DEBUG > 1) printf("debug {i:%d, j:%d} chamara checkMovesFromAllDirections\n", i, j);
                unsigned short int a = checkMovesFromAllDirections(matrix, i, j);
                if (DEBUG > 1) printf("debug {i:%d, j:%d} checkMovesFromAllDirections retornou %d\n", i, j, a);
                for (int k = 0; k < 4; k++) {
                    if (a & (1 << k)) {
                        int rowDummy = i - directions[k][0];
                        int colDummy = j - directions[k][1];
                        int** shapeCells = allocShapeCells();
                        if (shapeCells == NULL) {
                            if (DEBUG > 1) { printf("problema alocando shapeCells"); }
                            free(allMoves);
                            return NULL;
                        }
                        getShapeCells(matrix, rowDummy, colDummy, matrix[rowDummy][colDummy], shapeCells);
                        char** newMatrix = allocMatrix(MATRIX_ROWS, MATRIX_COLS);
                        if (newMatrix == NULL) {
                            if (DEBUG > 1) { printf("problema alocando newMatrix"); }
                            deleteShapeCells(shapeCells);
                            free(allMoves);
                            return NULL;
                        }
                        copyMatrix(matrix, newMatrix, MATRIX_ROWS, MATRIX_COLS);
                        moveShape(newMatrix, shapeCells, matrix[rowDummy][colDummy], k);
                        deleteShapeCells(shapeCells);
                        allMoves[(*n)++] = newMatrix;
                    }
                }
            }
        }
    }
    return allMoves;
}

// return an array of pointers related to all directions
unsigned short int checkMovesFromAllDirections(char** matrix, int i, int j) {
    unsigned short int possibleDirections = 0;
    for (int k = 0; k < 4; k++) {
        int rowDummy = i - directions[k][0];
        int colDummy = j - directions[k][1];
        int debuging = checkBoundaries(rowDummy, colDummy);
        if (DEBUG > 1) {
            printf("rowDummy: %d, colDummy: %d\n", rowDummy, colDummy);
            printf("checkBoundaries: %d\t%c\n", debuging, debuging ? matrix[rowDummy][colDummy] : ' ');
        }
        if (checkBoundaries(rowDummy, colDummy) && matrix[rowDummy][colDummy] != BLANK_SPACE) {
            int possible = checkShapeCanMove(matrix, rowDummy, colDummy, k);
            possibleDirections |= possible << k;
        }
    }
    if (DEBUG > 1) {
        printf("possibleDirections: %d\n", possibleDirections);
    }
    return possibleDirections;
}

int checkWanted(char** matrix, struct Target* wanted) {
    for (int i = 0; i < wanted->nLocations; i++) {
        if (matrix[wanted->locations[i][0]][wanted->locations[i][1]] != wanted->wantedChar) {
            return 0;
        }
    }
    return 1;
}

int checkWantedAllowed(struct Target* wanted) {
    for (int i = 0; i < wanted->nLocations; i++) {
        if (!checkBoundaries(wanted->locations[i][0], wanted->locations[i][1])) {
            return 0;
        }
    }
    return 1;
}

int* locateWanted(char** matrix, char wanted) {
    for (int i = MATRIX_ROWS - 1; i >= 0; i--) {
        for (int j = MATRIX_COLS - 1; j >= 0; j--) {
            if (matrix[i][j] == wanted) {
                int* local = (int*) malloc(2 * sizeof(int));
                if (local == NULL) {
                    return NULL;
                }
                local[0] = i;
                local[1] = j;
                return local;
            }
        }
    }
    return NULL;
}

int getDistanceValue(char** matrix, struct Target* wanted) {
    int distance = 0;
    int* l = locateWanted(matrix, wanted->wantedChar);
    if (l == NULL) {
        printf("error allocating locateWanted in getDistanceValue\n");
        return -1;
    }
    int** shapeCells = allocShapeCells();
    if (shapeCells == NULL) {
        free(l);
        printf("error allocating shapeCells in getDistanceValue\n");
        return -1;
    }
    getShapeCells(matrix, l[0], l[1], wanted->wantedChar, shapeCells);
    int** initRef = shapeCells;
    for (; *shapeCells; shapeCells++) {
        for (int i = 0; i < wanted->nLocations; i++) {
            distance += abs((*shapeCells)[0] - wanted->locations[i][0]) + abs((*shapeCells)[1] - wanted->locations[i][1]);
        }
    }
    deleteShapeCells(initRef);
    free(l);
    return distance;
}

// https://stackoverflow.com/questions/9846920/define-array-in-c
// https://www.geeksforgeeks.org/c-user-defined-data-types/
// https://www.geeksforgeeks.org/void-pointer-c-cpp/