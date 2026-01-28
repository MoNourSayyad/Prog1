#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#include "../prog1lib/lib/base.h"

typedef struct dynamic_stack_s {
    char* parenthesis;
    int size;
    int capacity;
} DynamicStack;

DynamicStack* stack_new();

void stack_free(DynamicStack* stack);

void stack_push(DynamicStack* stack, char parenthesis);

char stack_pop(DynamicStack* stack);

bool stack_is_empty(DynamicStack* stack);

char stack_peek(DynamicStack* stack);

#endif