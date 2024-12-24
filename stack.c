//
// Created by Predo on 24/12/2024.
//

#include "stack.h"

#include <stdlib.h>
#include <string.h>

char** allocStack() {
    char** stack = (char**)malloc(STACK_SIZE * sizeof(char*));
    for (int i = 0; i < STACK_SIZE; i++) {
        stack[i] = NULL;
    }
    return stack;
}

void push(char** stack, char* str) {
    for (int i = 0; i < STACK_SIZE; i++) {
        if (stack[i] == NULL) {
            stack[i] = str;
            return;
        }
    }
}

char* pop(char** stack) {
    for (int i = STACK_SIZE - 1; i >= 0; i--) {
        if (stack[i] != NULL) {
            char* str = stack[i];
            stack[i] = NULL;
            return str;
        }
    }
    return NULL;
}

int contains(char** stack, char* str) {
    for (int i = 0; i < STACK_SIZE; i++) {
        if (stack[i] != NULL && strcmp(stack[i], str) == 0) {
            return 1;
        }
    }
    return 0;
}

int getTail(char** stack) {
    if (stack[0] == NULL) {
        return -1;
    }
    for (int i = 0; i< STACK_SIZE; i++) {
        if (stack[i] == NULL) {
            return i - 1;
        }
    }
}