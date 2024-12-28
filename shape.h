//
// Created by Predo on 23/12/2024.
//

#ifndef SHAPE_H
#define SHAPE_H


int** allocShapeCells();
void moveShape(char** matrix, int** shapeCells, char dummy, int direction);
void deleteShapeCells(int** shapeCells);
int checkShapeCanMove(char** matrix, int i, int j, int direction);
void getShapeCells(char** matrix, int i, int j, char dummy, int** shapeCells);

#endif //SHAPE_H
