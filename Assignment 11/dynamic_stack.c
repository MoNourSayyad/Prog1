/*
    Compile: make dynamic_stack
    Run: ./dynamic_stack
    make dynamic_stack && ./dynamic_stack
*/

#include "../prog1lib/lib/base.h"
#include "dynamic_stack.h"


DynamicStack* stack_new() {
    DynamicStack* stack = xmalloc(sizeof(DynamicStack));
    stack->parenthesis = NULL;
    stack->size = 0;
    stack->capacity = 0;
    return stack;
}

void stack_free(DynamicStack* stack) {
    if (stack == NULL)
        return;
    if (stack->parenthesis != NULL)
        free(stack->parenthesis);
    free(stack);
    
}

void stack_push(DynamicStack* stack, char para) {
    if (stack->size == stack->capacity) {
        int newCapacity = (stack->capacity == 0) ? 1 : stack->capacity * 2;  // A new format i learned recently :) 
    // and I find that it's a good practice to double the capactity when it's full.
    char* newPara = xrealloc(stack->parenthesis, newCapacity * sizeof(char)); // I also recently learned that realloc is a func that's used for Increasing the spaced of allocated area. (xrealloc is in Proglib)
    stack->parenthesis = newPara;
    stack->capacity = newCapacity;
    }
    stack->parenthesis[stack->size] = para;
    stack->size++;
}

char stack_pop(DynamicStack* stack) {
    if (stack->size == 0)
        return '\0';
    stack->size--; // Cuz its an array from 0 to n-1
    return stack->parenthesis[stack->size]; 
}

bool stack_is_empty(DynamicStack* stack) {
    return stack->size == 0;
}

char stack_peek(DynamicStack* stack) {
    if (stack->size == 0) return '\0';
    return stack->parenthesis[stack->size - 1];
}

