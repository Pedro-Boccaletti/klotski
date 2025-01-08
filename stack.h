//
// Created by Predo on 24/12/2024.
//

#ifndef STACK_H
#define STACK_H
#define STACK_SIZE 300000
char** allocStack();
void push(char** stack, int* index, char* str);
char* pop(char** stack, int* index);
int contains(char** stack, int* index, char* str);

#endif //STACK_H
