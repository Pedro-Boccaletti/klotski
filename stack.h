//
// Created by Predo on 24/12/2024.
//

#ifndef STACK_H
#define STACK_H
#define STACK_SIZE 300000
#include <stdint.h>
uint32_t* allocStack();
void push(uint32_t* stack, int* index, uint32_t hash);
uint32_t pop(uint32_t* stack, int* index);
int contains(uint32_t* stack, int* index, uint32_t hash);

#endif //STACK_H
