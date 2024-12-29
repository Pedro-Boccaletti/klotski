//
// Created by Predo on 24/12/2024.
//

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

char** allocStack() {
    char** stack = (char**)malloc(STACK_SIZE * sizeof(char*));
    for (int i = 0; i < STACK_SIZE; i++) {
        stack[i] = NULL;
    }
    return stack;
}

void push(char** stack, int* index, char* str) {
    if (*index == STACK_SIZE - 1) {
        printf("Stack is full\n");
        exit(-1);
    }
    if (stack[*index] == NULL) {
        if (DEBUG) {
            printf("debug {i:%d, str:%s}\n", *index, str);
        }
        stack[*index++] = str;
        return;
    }
    printf("problem in Stack\n");
    exit(-1);
}

char* pop(char** stack, int* index) {
    if (stack[*index] != NULL) {
        char* str = stack[*index];
        stack[*index--] = NULL;
        return str;
    }
    return NULL;
}

int contains(char** stack, int* index, char* str) {
    for (int i = 0; i < *index; i++) {
        if (stack[i] != NULL && strcmp(stack[i], str) == 0) {
            return 1;
        }
    }
    return 0;
}
