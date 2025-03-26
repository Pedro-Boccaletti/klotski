//
// Created by Predo on 24/12/2024.
//

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

uint32_t* allocStack() {
    uint32_t* stack = (uint32_t*)malloc(STACK_SIZE * sizeof(uint32_t));
    return stack;
}

void push(uint32_t* stack, int* index, uint32_t hash) {
    if (*index == STACK_SIZE - 1) {
        printf("Stack is full\n");
        exit(-1);
    }
    stack[(*index)++] = hash;
}

uint32_t pop(uint32_t* stack, int* index) {
    if (*index == 0) {
        if (DEBUG > 1) printf("Stack is empty\n");
        exit(5);
    }
    return stack[--(*index)];
}

int contains(uint32_t* stack, int* index, uint32_t hash) {
    for (int i = 0; i < *index; i++) {
        if (stack[i] == hash) {
            return 1;
        }
    }
    return 0;
}
