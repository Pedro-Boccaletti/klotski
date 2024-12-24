//
// Created by Predo on 24/12/2024.
//

#ifndef STACK_H
#define STACK_H
#define STACK_SIZE 100000
char** allocStack();
void push(char** stack, char* str);
char* pop(char** stack);
int contains(char** stack, char* str);
int getTail(char** stack);

#endif //STACK_H
