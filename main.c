#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "matrix.h"
#include "shape.h"
#include "stack.h"
#include <time.h>


time_t start;

int test(char**);

int main(void)
{
    char** matrix = allocMatrix(MATRIX_ROWS, MATRIX_COLS);
    if (matrix == NULL) {
        return 1;
    }
    start = time(NULL);
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            setMatrixValue(matrix, i, j, initialMatrix[i][j]);
        }
    }
    uint32_t* testedStack = allocStack();
    if (testedStack == NULL) {
        return 1;
    }

    struct Target* wanted = (struct Target*) malloc(sizeof(struct Target));
    wanted->wantedChar = 'D';
    int locations[1][2] = { { MATRIX_ROWS - 1, MATRIX_COLS - 1 } };
    wanted->locations = locations;
    wanted->nLocations = 1;
    if (!checkWantedAllowed(wanted)) {
        return 1;
    }
    int stackIndex = 0;

    MatrixNode* matrixNode = createMatrixNode(matrix);
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

// função para fazer o loop recursivamente
void loop(MatrixNode* matrixNode, uint32_t* checkedStack, int* stackIndex, struct Target* wanted, int depth, int optimizationNumber) {
    if (optimizationNumber > OPTIMIZATION_NUMBER) {
        deleteMatrix(matrixNode->data, MATRIX_ROWS);
        free(matrixNode);
        return;
    }
    char** matrix = matrixNode->data;
    if (depth >= MAX_DEPTH) {
        if (DEBUG > 1) printf("max depth reached\n");
        return;
    }
    if (DEBUG > 1) {
        printMatrix(matrix, MATRIX_ROWS, MATRIX_COLS);
    }
    if (DEBUG) {
        time_t now = time(NULL);
        printf("tempo de execução: %ld segundos\n", now - start);
    }
    if (checkWanted(matrix, wanted)) {
        if (DEBUG) printf("achou\n");
        printAnswer(matrixNode, SECONDS_PRINT_ANSWER);
        printf("encontrado com %d movimentos\n", depth);
        time_t end = time(NULL);
        printf("tempo de execução: %ld segundos\n", end - start);
        exit(0);
    }
    int distance = getDistanceValue(matrix, wanted);
    if (distance == -1) {
        printf("deu BO getDistanceValue\n");
        exit(-2);
    }
    matrixNode->distance = distance;
    if (matrixNode->parent) {
        if (matrixNode->parent->distance < matrixNode->distance) {
            optimizationNumber++;
        } else if (matrixNode->parent->distance > matrixNode->distance) {
            optimizationNumber = 0;
        }
    }

    uint32_t hash = hashMatrix(matrixNode, MATRIX_ROWS, MATRIX_COLS);
    if (contains(checkedStack, stackIndex, hash)) {
        if (DEBUG > 1) printf("debug {hash:%d} already in stack\n", hash);
        return;
    }
    push(checkedStack, stackIndex, hash);
    // check all possible moves
    int nMoves = 0;
    char*** newMatrices = checkAllMoves(matrix, &nMoves);
    for (int i = 0; i < nMoves; i++) {
        MatrixNode* node = createMatrixNode(newMatrices[i]);
        node->parent = matrixNode;
        loop(node, checkedStack, stackIndex, wanted, depth + 1, optimizationNumber);
    }
    free(newMatrices);
    deleteMatrix(matrix, MATRIX_ROWS);
    free(matrixNode);
}

// check all possible moves, returns a pointer to a pointer of the new matrixes created and places the number of matrixes created in the pointer n
char*** checkAllMoves(char** matrix, int* n) {
    // allocate memory for the pointer to the pointer of the new matrixes
    size_t size = 4 * BLANK_SPACE_AMOUNT * sizeof(char**);
    char*** allMoves = (char***) malloc(size);
    if (allMoves == NULL) {
        return NULL;
    }

    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLS; j++) {
            if (matrix[i][j] == BLANK_SPACE) {
                if (DEBUG > 1) printf("debug {i:%d, j:%d} chamara checkMovesFromAllDirections\n", i, j);
                unsigned short int possibleMoves = checkMovesFromAllDirections(matrix, i, j);
                if (DEBUG > 1) printf("debug {i:%d, j:%d} checkMovesFromAllDirections retornou %d\n", i, j, possibleMoves);
                // check all directions
                for (int k = 0; k < 4; k++) {
                    // if the direction is possible (bit is set)
                    if (possibleMoves & (1 << k)) {
                        // get the shape from the possible direction
                        int rowDummy = i - directions[k][0];
                        int colDummy = j - directions[k][1];
                        int** shapeCells = allocShapeCells();
                        if (shapeCells == NULL) {
                            if (DEBUG > 1) { printf("problema alocando shapeCells"); }
                            free(allMoves);
                            return NULL;
                        }
                        getShapeCells(matrix, rowDummy, colDummy, matrix[rowDummy][colDummy], shapeCells);

                        // alloc a new matrix
                        char** newMatrix = allocMatrix(MATRIX_ROWS, MATRIX_COLS);
                        if (newMatrix == NULL) {
                            if (DEBUG > 1) { printf("problema alocando newMatrix"); }
                            deleteShapeCells(shapeCells);
                            free(allMoves);
                            return NULL;
                        }
                        //copy the current matrix to the new matrix and move the shape
                        copyMatrix(matrix, newMatrix, MATRIX_ROWS, MATRIX_COLS);
                        moveShape(newMatrix, shapeCells, matrix[rowDummy][colDummy], k);
                        // free the shape cells
                        deleteShapeCells(shapeCells);
                        // add the new matrix to the allMoves pointer and inc n
                        allMoves[(*n)++] = newMatrix;
                    }
                }
            }
        }
    }
    return allMoves;
}

// return a bit mask of pointers related to all directions (bit 0 -> right, bit 1 -> down, bit 2 -> left, bit 3 -> up)
// i and j are the row and column of the blank space
unsigned short int checkMovesFromAllDirections(char** matrix, int i, int j) {
    unsigned short int possibleDirections = 0;
    // check all directions
    for (int k = 0; k < 4; k++) {
        int rowDummy = i - directions[k][0];
        int colDummy = j - directions[k][1];
        if (DEBUG > 1) {
            int debuging = checkBoundaries(rowDummy, colDummy);
            printf("rowDummy: %d, colDummy: %d\n", rowDummy, colDummy);
            printf("checkBoundaries: %d\t%c\n", debuging, debuging ? matrix[rowDummy][colDummy] : ' ');
        }
        // if the row and column are within the matrix boundaries and the cell is not a blank space
        if (checkBoundaries(rowDummy, colDummy) && matrix[rowDummy][colDummy] != BLANK_SPACE) {
            int possible = checkShapeCanMove(matrix, rowDummy, colDummy, k);
            // set the bit of the direction if the shape can move in that direction
            possibleDirections |= possible << k;
        }
    }
    if (DEBUG > 1) {
        printf("possibleDirections: %d\n", possibleDirections);
    }
    return possibleDirections;
}

// check if the wanted char is in the wanted locations
int checkWanted(char** matrix, struct Target* wanted) {
    for (int i = 0; i < wanted->nLocations; i++) {
        if (matrix[wanted->locations[i][0]][wanted->locations[i][1]] != wanted->wantedChar) {
            return 0;
        }
    }
    return 1;
}

// check if the wanted locations are within the matrix boundaries
int checkWantedAllowed(struct Target* wanted) {
    for (int i = 0; i < wanted->nLocations; i++) {
        if (!checkBoundaries(wanted->locations[i][0], wanted->locations[i][1])) {
            return 0;
        }
    }
    return 1;
}

// return the first cell location of the wanted char found in the matrix (mainly used to then get all the shape cells)
int* locateChar(char** matrix, char wanted) {
    for (int i = MATRIX_ROWS - 1; i >= 0; i--) {
        for (int j = MATRIX_COLS - 1; j >= 0; j--) {
            if (matrix[i][j] == wanted) {
                int* local = (int*) malloc(2 * sizeof(int));
                if (local == NULL) {
                    printf("problem allocating memory for local in locateWanted\n");
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

// return the sum of the distances of the shape cells to the wanted locations
int getDistanceValue(char** matrix, struct Target* wanted) {
    int distance = 0;
    int* l = locateChar(matrix, wanted->wantedChar);
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